#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <queue>
#include <mutex>
extern "C" {
    #include <libavcodec/avcodec.h>
}

#include <condition_variable>
class PacketQueue {
    public:
        PacketQueue(size_t maxSize);
        ~PacketQueue();

        void push(const AVPacket& packet);
        bool pop(AVPacket& packet);

        void stop();
        void clear();
              
        bool empty() const;
        size_t size() const;

    private:

        std::queue<AVPacket> queue_; 
        
        mutable std::mutex mutex_;//互斥锁
        std::condition_variable cv_;

        bool running_;
        size_t maxSize_;//队列最大容量
};

#endif