#ifndef FRAME_QUEUE_H
#define FRAME_QUEUE_H

extern "C" {
    #include <libavutil/frame.h>
} 
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
class FrameQueue {
    public:
        FrameQueue(size_t maxSize);
        ~FrameQueue();

        AVFrame* pop();
        void push(AVFrame* frame);

        void stop();
        void clear();

        size_t size() const;
        bool empty() const;

    private:
        std::queue<AVFrame* > queue_;

        mutable std::mutex mutex_;
        std::condition_variable cv_;

        size_t maxSize_;
        bool running_;
};

#endif