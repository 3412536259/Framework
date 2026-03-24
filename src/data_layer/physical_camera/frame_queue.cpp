#include "data_layer/physical_camera/frame_queue.h"

FrameQueue::FrameQueue(size_t maxSize) 
    : maxSize_(maxSize),running_(true){

}
FrameQueue::~FrameQueue() {
    stop();
    clear();
}

AVFrame* FrameQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex_);

    cv_.wait(lock,[this] {
        return !queue_.empty() || !running_;
    });

    if(!running_ && queue_.empty())
        return nullptr;
    
    AVFrame* frame = queue_.front();
    queue_.pop();
    return frame;
}

void FrameQueue::push(AVFrame* frame) {
    std::unique_lock<std::mutex> lock(mutex_);

    while(queue_.size() >= maxSize_) {
        AVFrame* old = queue_.front();
        av_frame_free(&old);
        queue_.pop();
    }
    queue_.push(frame);
    cv_.notify_one();
}

void FrameQueue::stop() {
    
    std::lock_guard<std::mutex> lock(mutex_);
    running_ = false;
    cv_.notify_all();
}
void FrameQueue::clear() {
    std::lock_guard<std::mutex> lock(mutex_);

    while (!queue_.empty()) {
        AVFrame* frame = queue_.front();
        av_frame_free(&frame);
        queue_.pop();
    }
}

size_t FrameQueue::size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}
bool FrameQueue::empty() const {
    return queue_.empty();
}