#include "data_layer/stream_nvr/puller_stream.h"
#include "common/log/log_manager.h"
HikvisionPuller::HikvisionPuller(const std::string userId, int channel){

}

HikvisionPuller::~HikvisionPuller(){

}

bool HikvisionPuller::open(){
    std::lock_guard<std::mutex> lock(mutex_);

    if (opened_) {
        return true;
    }

    if (userId_ < 0) {
        std::cerr << "[HikvisionPuller::open] invalid userId_" << std::endl;
        return false;
    }


    if (!initDecoder()) {
        std::cerr << "[HikvisionPuller::open] initDecoder failed" << std::endl;
        return false;
    }
    opened_ = true;

     return true;
}

bool HikvisionPuller::readFrame(FrameData& FrameData){
    return true;
}

bool HikvisionPuller::readFrameTime(FrameData& FrameData, int timeoutMs) {
    return true;
}


void HikvisionPuller::close() {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!opened_) {
        return;
    }

    if (started_ && realHandle_ >= 0) {
        NET_DVR_StopRealPlay(realHandle_);
        realHandle_ = -1;
        started_ = false;
    }

    // releaseDecoder();
    // queue_->clear();

    opened_ = false;

    std::cout << "[HikvisionPuller::close] close success" << std::endl;
}


bool HikvisionPuller::start() {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!opened_) {
        std::cerr << "[HikvisionPuller::start] not opened" << std::endl;
        return false;
    }

    if (started_) {
        return true;
    }

    NET_DVR_PREVIEWINFO previewInfo;
    std::memset(&previewInfo, 0, sizeof(previewInfo));

    previewInfo.lChannel = channel_;
    previewInfo.dwStreamType = 0;   // 主码流
    previewInfo.dwLinkMode = 0;     // TCP
    previewInfo.hPlayWnd = 0; // 不显示窗口
    previewInfo.bBlocked = 1;

    realHandle_ = NET_DVR_RealPlay_V40(
        userId_,
        &previewInfo,
        RealDataCallback,
        this
    );

    if (realHandle_ < 0) {
        DWORD err = NET_DVR_GetLastError();
        std::cerr << "[HikvisionPuller::start] NET_DVR_RealPlay_V40 failed, err=" << err << std::endl;
        return false;
    }

    started_ = true;

    std::cout << "[HikvisionPuller::start] start success, realHandle=" << realHandle_ << std::endl;
    return true;
}

bool HikvisionPuller::stop() {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!started_) {
        return true;
    }

    if (realHandle_ >= 0) {
        if (!NET_DVR_StopRealPlay(realHandle_)) {
            DWORD err = NET_DVR_GetLastError();
            std::cerr << "[HikvisionPuller::stop] NET_DVR_StopRealPlay failed, err=" << err << std::endl;
            return false;
        }
        realHandle_ = -1;
    }

    started_ = false;

    std::cout << "[HikvisionPuller::stop] stop success" << std::endl;
    return true;
}

void CALLBACK HikvisionPuller::RealDataCallback(LONG lRealHandle,DWORD dwDataType,BYTE* pBuffer,DWORD dwBufSize,void* pUser){
    if (!pUser || !pBuffer || dwBufSize == 0) {
        return;
    }

    auto* self = static_cast<HikvisionPuller*>(pUser);
    self->handleRealData(dwDataType, pBuffer, dwBufSize);
}

void HikvisionPuller::handleRealData(DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize) {
    if (!pBuffer || dwBufSize == 0) return;

    switch (dwDataType) {
        case NET_DVR_SYSHEAD:
            // 如果需要，可在这里初始化PS/ES解析器
            break;

        case NET_DVR_STREAMDATA:
            onEncodedFrame(reinterpret_cast<uint8_t*>(pBuffer), dwBufSize);
            break;

        default:
            break;
    }
}


bool HikvisionPuller::initDecoder() {
    // LOG_INFO("[Camera::initDecoder] 开始初始化解码器，通道号：" + std::to_string(info_.channel));

    // 分配解码器上下文
    codecCtx_ = avcodec_alloc_context3(nullptr);
    if (!codecCtx_) {
        // LOG_ERROR("[Camera::initDecoder] 分配解码器上下文失败，通道号：" + std::to_string(info_.channel));
        return false;
    }

    // 开启自动检测编码格式
    codecCtx_->flags2 |= AV_CODEC_FLAG2_CHUNKS;
    // LOG_INFO("[Camera::initDecoder] 解码器上下文初始化成功，已开启自动检测编码格式，通道号：" + std::to_string(info_.channel));

    // 初始化YUV帧（补充：原代码未初始化frameYUV_，建议添加）
    frameYUV_ = av_frame_alloc();
    if (!frameYUV_) {
        // LOG_ERROR("[Camera::initDecoder] 分配YUV帧失败，通道号：" + std::to_string(info_.channel));
        avcodec_free_context(&codecCtx_);
        codecCtx_ = nullptr;
        return false;
    }

    decoderInitialized_ = false; // 初始化为未初始化状态
    return true;
}

void HikvisionPuller::onEncodedFrame(uint8_t* data, size_t len) {
    if (!data || len == 0 || !codecCtx_) {
        // updateStatus(CameraStatus::OFFLINE);
        return;
    }
  
    if (!decoderInitialized_) { // 1. 解码器初始化（第一次收到有效码流时）
        AVCodecID id = detectCodec(data, len);
        if (id == AV_CODEC_ID_NONE) {
            std::cerr << "[Camera] 未检测到有效编码类型" << std::endl;
            return;
        }

        const AVCodec* codec = avcodec_find_decoder(id);
        codecCtx_->codec_id = id;
        codecCtx_->codec_type = AVMEDIA_TYPE_VIDEO;

        if (avcodec_open2(codecCtx_, codec, nullptr) < 0) {
            return;
        }
        decoderInitialized_ = true;
    }
  
     // 2. 安全构造 AVPacket（复制数据）
    AVPacket* pkt = av_packet_alloc();
    if (!pkt) {
        return;
    }

    if (av_new_packet(pkt, static_cast<int>(len)) < 0) {
        av_packet_free(&pkt);
        return;
    }

    std::memcpy(pkt->data, data, len);

    // 发送数据包到解码器（加锁避免多线程冲突）
    int ret = 0;
    {
        std::lock_guard<std::mutex> lock(decoderMutex_);
        ret = avcodec_send_packet(codecCtx_, pkt);
    }

    if (ret < 0) {
        // logFFmpegError("avcodec_send_packet", ret);
        av_packet_free(&pkt);
        // updateStatus(CameraStatus::OFFLINE);
        return;
    }

    // 接收解码后的帧
    {
        std::lock_guard<std::mutex> lock(decoderMutex_);
        ret = avcodec_receive_frame(codecCtx_, frameYUV_);
    }

    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        av_packet_free(&pkt);
        return;
    } else if (ret < 0) {
        // logFFmpegError("avcodec_receive_frame", ret);
        av_packet_free(&pkt);
        // updateStatus(CameraStatus::OFFLINE);
        return;
    }
    
    // 只处理关键帧（保留YUV原始帧，删除RGB转换）
    if (frameYUV_->key_frame == 1) {
        // 验证YUV帧数据有效性
        if (!frameYUV_->data[0] || !frameYUV_->data[1] || !frameYUV_->data[2]) {
            // std::cerr << "[Camera] 通道" << info_.channel << " YUV帧指针为空" << std::endl;
            av_packet_free(&pkt);
            return;
        }

        // 直接保存YUV关键帧（不再转换为RGB）
        AVFrame* keyFrameCopy = av_frame_clone(frameYUV_);
        if (!keyFrameCopy) {
            std::cerr << "Failed to clone frameYUV_ for lastKeyFrame_" << std::endl;
        } else {
            std::lock_guard<std::mutex> lock(frameMutex_);  // 改用frameMutex_（删除了frameRGBMutex_）
            lastKeyFrame_.frame = std::shared_ptr<AVFrame>(keyFrameCopy, [](AVFrame* f){
                av_frame_free(&f);
            });
            lastKeyFrame_.width = frameYUV_->width;
            lastKeyFrame_.height = frameYUV_->height;
            lastKeyFrame_.lastKeyFrameTime = av_gettime_relative();
            lastKeyFrame_.valid = true;
        }

        av_packet_free(&pkt);
        // 重置YUV帧（准备接收下一帧）
        av_frame_unref(frameYUV_);
    }
}

std::shared_ptr<FrameData> HikvisionPuller::getLatestFrame() {
    std::lock_guard<std::mutex> lock(frameMutex_);

    if (!lastKeyFrame_.valid || !lastKeyFrame_.frame) {
        return  nullptr;
    }

    // 深拷贝一份给外部，避免外部拿到后被内部覆盖
    AVFrame* cloned = av_frame_clone(lastKeyFrame_.frame.get());
    if (!cloned) {
        return  nullptr;
    }
    auto outFrame = std::make_shared<FrameData>();

    outFrame->frame = std::shared_ptr<AVFrame>(cloned, [](AVFrame* f) {
        av_frame_free(&f);
    });
    outFrame->width = lastKeyFrame_.width;
    outFrame->height = lastKeyFrame_.height;
    outFrame->lastKeyFrameTime = lastKeyFrame_.lastKeyFrameTime;
    outFrame->valid = true;

    return outFrame;
}

AVCodecID HikvisionPuller::detectCodec(uint8_t* data, size_t len) {
    // LOG_INFO("[Camera::detectCodec] 检测编码类型，通道号：" + std::to_string(info_.channel) + 
    //          "，数据长度：" + std::to_string(len) + "字节");

    if (len < 5) {
        // LOG_WARNING("[Camera::detectCodec] 数据长度不足（<5字节），无法检测编码类型，通道号：" + std::to_string(info_.channel));
        return AV_CODEC_ID_NONE;
    }
    // AnnexB 00 00 00 01
    if (data[0] == 0x00 && data[1] == 0x00 && data[2] == 0x00 && data[3] == 0x01) {
        uint8_t nal = data[4];
        // LOG_INFO("[Camera::detectCodec] 检测到AnnexB格式NALU头，NAL类型：0x" + std::to_string(nal) + 
        //          "，通道号：" + std::to_string(info_.channel));

        if ((nal & 0x1F) == 7) {
            // LOG_INFO("[Camera::detectCodec] 检测到H264 SPS，通道号：" + std::to_string(info_.channel));
            return AV_CODEC_ID_H264; // H264 SPS
        }
        if ((nal >> 1) == 0x20) {
            // LOG_INFO("[Camera::detectCodec] 检测到H265 VPS，通道号：" + std::to_string(info_.channel));
            return AV_CODEC_ID_HEVC; // H265 VPS
        }
    }

    // LOG_WARNING("[Camera::detectCodec] 未识别的编码类型（非H264/H265），通道号：" + std::to_string(info_.channel));
    return AV_CODEC_ID_NONE;
}