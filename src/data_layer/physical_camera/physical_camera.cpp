#include "data_layer/physical_camera/physical_camera.h"

#include <iostream>
PhysicalCamera::PhysicalCamera(const std::string& cameraId,
                       const std::string& rtspUrl,
                       std::shared_ptr<PacketQueue> packetQueue,
                       std::unique_ptr<PacketDecoder> packetDecoder,
                       std::unique_ptr<StreamPuller> streamPuller)
    : cameraId_(cameraId),
      rtspUrl_(rtspUrl),
      packetQueue_(std::move(packetQueue)),
      packetDecoder_(std::move(packetDecoder)),
      streamPuller_(std::move(streamPuller)),
      running_(false) {
    streamPuller_ -> setPacketQueue(packetQueue_);
}

PhysicalCamera::~PhysicalCamera() {

}

void PhysicalCamera::startStreamPull() {
    if(running_) return ;

    running_ = true;

    

    if(!streamPuller_ -> open()) {
        running_ = false;
        return ;
    }

    streamPuller_ -> start();

    decodeThread_ = std::thread(&PhysicalCamera::pullLoop,this);
    recordThread_ = std::thread(&PhysicalCamera::recordLoop, this);

}
void PhysicalCamera::stopStreamPull() {
    if(!running_) return;

    running_ = false;

    streamPuller_ -> stop();

    packetQueue_ -> stop();
    // frameQueue_ -> stop();

    if(decodeThread_.joinable())
        decodeThread_.join();
    
    if (recordThread_.joinable())
        recordThread_.join();

    packetQueue_ -> clear();
    // frameQueue_ -> clear();

    packetDecoder_ -> flush();
}
    
 
void PhysicalCamera::pullLoop() {
    while (running_) {
        AVPacket packet;

        if(!packetQueue_ -> pop(packet))
            continue;

        std::vector<AVFrame*> frames;
        if(!packetDecoder_ -> decode(&packet,frames))
            continue;

        VideoPacket vp;
        av_packet_ref(&vp.pkt,&packet);

        vp.timestamp = nowMs();
        vp.isKeyFrame = (packet.flags & AV_PKT_FLAG_KEY);
        storePacket(vp);
        av_packet_unref(&packet);
        
        for(auto* frame : frames) {
            if(!frame) continue;
            if(frame->width ==0 || frame->height == 0) continue;
            if(!frame ->data[0] ) continue;
            int64_t ts = av_frame_get_best_effort_timestamp(frame);

            AVFrame* cloned = av_frame_clone(frame);
            std::shared_ptr<AVFrame> framePtr(
                cloned,
                [](AVFrame* f) {
                    if(f) av_frame_free(&f);
                }
            );
            
            //获取关键帧
            if(frame -> key_frame == 1 || frame->pict_type == AV_PICTURE_TYPE_I) {
                KeyFrame keyFrame;
                keyFrame.cameraId = cameraId_;
                keyFrame.frame = framePtr;
                keyFrame.timestamp = ts;
                dispater_.dispaterKeyFrame(keyFrame);
            }
        }

    }
    
}

void PhysicalCamera::storePacket(const VideoPacket& pkt) {
    std::lock_guard<std::mutex> lock(bufferMutex_);

    videoPacketBuffer_.push_back(pkt);
    int64_t newest = pkt.timestamp;

    while(!videoPacketBuffer_.empty()) {
        if(newest - videoPacketBuffer_.front().timestamp > MAX_BUFFER_MS) {
            av_packet_unref(&videoPacketBuffer_.front().pkt);
            videoPacketBuffer_.pop_front();
        }
        else break;
    }
    
}
void PhysicalCamera::recordLoop() {
    std::cout << "开始视频生成" <<std::endl;
    std::unique_lock<std::mutex> lock(recordMutex_);
    while(running_) {
        std::this_thread::sleep_for(std::chrono::minutes(1));
        if(!running_) break;
        generateHistoryVideo();
    }
    
}
void PhysicalCamera::generateHistoryVideo() {
    int64_t end = nowMs();
    int64_t start = end - 60 * 1000;
    std::vector<VideoPacket> packets;

    {
        std::lock_guard<std::mutex> lock(bufferMutex_);
        for(auto& p : videoPacketBuffer_) {
            VideoPacket vp;
            av_packet_ref(&vp.pkt,&p.pkt);
            vp.timestamp = p.timestamp;
            vp.isKeyFrame = p.isKeyFrame;

            int64_t safeStart = start - 3000; 
            if(p.timestamp >= safeStart && p.timestamp <= end)
                packets.push_back(std::move(vp));
        }
    }
   

    if(packets.empty())
        return;

    int startIndex = -1;
    for(int i = packets.size() - 1; i >= 0; --i) {
        if(packets[i].timestamp <= start &&
           (packets[i].pkt.flags & AV_PKT_FLAG_KEY)) {
            startIndex = i;
            break;
        }
    }

    if (startIndex == -1) {
        for (int i = 0; i < packets.size(); ++i) {
            if (packets[i].pkt.flags & AV_PKT_FLAG_KEY) {
                startIndex = i;
                break;
            }
        }
    }

    int endIndex = packets.size() - 1;

    for (int i = startIndex + 1; i < packets.size(); ++i) {
        if (packets[i].timestamp > end &&
            (packets[i].pkt.flags & AV_PKT_FLAG_KEY)) {
            endIndex = i;
            break;
        }
    }

    if(startIndex == -1) return;

    std::string filename = cameraId_ + "_" + std::to_string(start) + ".mp4";
    
    AVStream* inStream = streamPuller_ -> getVideoStream();

    AVFormatContext* fmtCtx = nullptr;
    avformat_alloc_output_context2(&fmtCtx,nullptr,nullptr,filename.c_str());

    AVStream* outStream = avformat_new_stream(fmtCtx,nullptr);
    outStream->codecpar->codec_tag = 0;

    if(!inStream) return;
    if(!fmtCtx) return;
    if(!outStream) return;

    avcodec_parameters_copy(outStream->codecpar,inStream->codecpar);
    outStream -> time_base = inStream -> time_base;

    if(!(fmtCtx->oformat->flags & AVFMT_NOFILE)) {
        if(avio_open(&fmtCtx->pb,filename.c_str(),AVIO_FLAG_WRITE) < 0 ) {
            avformat_free_context(fmtCtx);
            return;
        }
    }

    avio_open(&fmtCtx -> pb,filename.c_str(),AVIO_FLAG_WRITE);
    if (avformat_write_header(fmtCtx, nullptr) < 0) {
        avio_closep(&fmtCtx->pb);
        avformat_free_context(fmtCtx);
        return;
    }

    int64_t firstDts = packets[startIndex].pkt.dts;
    if (firstDts == AV_NOPTS_VALUE)
        firstDts = packets[startIndex].pkt.pts;
    if (firstDts == AV_NOPTS_VALUE)
        firstDts = 0;

    for(int i = startIndex; i <= endIndex; ++i) {
        AVPacket pkt;
        av_packet_ref(&pkt,&packets[i].pkt);
        
        if (pkt.stream_index != inStream->index) {
            av_packet_unref(&pkt);
            continue;
        }

        if (pkt.dts != AV_NOPTS_VALUE)
            pkt.dts -= firstDts;
        if (pkt.pts != AV_NOPTS_VALUE)
            pkt.pts -= firstDts;

        if (pkt.dts < 0) pkt.dts = 0;
        if (pkt.pts < 0) pkt.pts = 0;

        av_packet_rescale_ts(&pkt,inStream -> time_base,outStream -> time_base);

        pkt.stream_index = outStream -> index;
        av_interleaved_write_frame(fmtCtx,&pkt);
        av_packet_unref(&pkt);
    }

    av_write_trailer(fmtCtx);
    avio_closep(&fmtCtx->pb);
    avformat_free_context(fmtCtx);

    for (auto& p : packets) {
        av_packet_unref(&p.pkt);
    }
}

int64_t PhysicalCamera::nowMs() {
    using namespace std::chrono;
    return duration_cast<milliseconds>( 
        steady_clock::now().time_since_epoch() 
    ).count();
}
 