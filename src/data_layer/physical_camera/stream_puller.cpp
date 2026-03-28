#include "data_layer/physical_camera/stream_puller.h"

StreamPuller::StreamPuller(const std::string& rtspUrl) {
    rtspUrl_ = rtspUrl;
}

bool StreamPuller::open() {
    avformat_network_init();

    if(avformat_open_input(&formatCtx_,rtspUrl_.c_str(),nullptr,nullptr) != 0)
        return false;
    
    if(avformat_find_stream_info(formatCtx_,nullptr) < 0) 
        return false;

    for(int i = 0; i < formatCtx_ -> nb_streams; i++) {
        if(formatCtx_ -> streams[i] -> codecpar -> codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex_ = i;
            break;
        }
    }
    return videoStreamIndex_ >= 0;
}

bool StreamPuller::start() {
    running_ = true;
    worker_ = std::thread(&StreamPuller::run,this);
}

bool StreamPuller::stop() {
    running_ = false;

    if(worker_.joinable())
        worker_.join();
    
    if(formatCtx_) {
        avformat_close_input(&formatCtx_);
        formatCtx_ = nullptr;
    }
}

void StreamPuller::setPacketQueue(std::shared_ptr<PacketQueue> queue) {

}

void StreamPuller::setReconnectTimeout(int seconds) {
    videoStreamIndex_ = seconds;
}

AVStream* StreamPuller::getVideoStream() {
    if(videoStreamIndex_ < 0) return nullptr;
    return formatCtx_ -> streams[videoStreamIndex_];
}

void StreamPuller::run() {
    while (running_) {
        AVPacket packet;
        av_init_packet(&packet);

        int ret = av_read_frame(formatCtx_,&packet);

        if(ret < 0) {
            av_packet_unref(&packet);

            if(!reconnect()) {
                std::this_thread::sleep_for(
                    std::chrono::seconds(reconnectTimeout_));
            }
            continue;
        }

        if(packet.stream_index == videoStreamIndex_) {
            packetQueue_ -> push(packet);
        } else {
            av_packet_unref(&packet);
        }
    }
    
}

bool StreamPuller::reconnect() {
    avformat_close_input(&formatCtx_);

    for(int i = 0;i < 3 && running_; i++) { 
        if(open())
            return true;
        std::this_thread::sleep_for(std::chrono::seconds(reconnectTimeout_));
    }
    return false;
}