#ifndef STREAM_PULLER_H
#define STREAM_PULLER_H

#include <string>
#include <memory>
#include <atomic>
#include <libavformat/avformat.h>
#include <thread>
#include "data_layer/physical_camera/packet_queue.h"
class StreamPuller {
    public:
        StreamPuller(std::string& rtspUrl);
        bool open();
        bool start();
        bool stop();

        void setPacketQueue(std::shared_ptr<PacketQueue> queue);
        void setReconnectTimeout(int seconds);
    
    private:
        void run();
        bool reconnect();

    private:

        std::string rtspUrl_;
        AVFormatContext* formatCtx_ = nullptr;//FFmpeg格式上下文
        int videoStreamIndex_ = -1;
        
        std::thread worker_;
        std::shared_ptr<PacketQueue> packetQueue_;
        std::atomic<bool> running_{false};

        int reconnectTimeout_ = 3;
};

#endif