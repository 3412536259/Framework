#include "data_layer/physical_camera/packet_queue.h"

PacketQueue::PacketQueue(size_t maxSize)
    : running_(true) {
    maxSize_ = maxSize;
}

PacketQueue::~PacketQueue() {
    stop();
    clear();
}

void PacketQueue::push(const AVPacket& packet) {
    std::unique_lock<std::mutex> lock(mutex_);

    if(queue_.size() >= maxSize_) {
        AVPacket old = queue_.front();
        av_packet_unref(&old);
        queue_.pop();
    }

    AVPacket copy;
    av_packet_ref(&copy,&packet);
    queue_.push(copy);

    cv_.notify_one();
}

bool PacketQueue::pop(AVPacket& packet) {
    std::unique_lock<std::mutex> lock(mutex_);

    cv_.wait(lock,[this] {
        return !queue_.empty() || !running_;
    });

    if(!running_ && queue_.empty())
        return false;
    
    packet = queue_.front();
    queue_.pop();
    return true;
}

void PacketQueue::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        running_ = false;
    }
    cv_.notify_all();
}

void PacketQueue::clear() {
    std::lock_guard<std::mutex> lock(mutex_);

    while (!queue_.empty()) {
        AVPacket packet = queue_.front();
        av_packet_unref(&packet);
        queue_.pop();
    }
    
}

bool PacketQueue::empty() const {
    return queue_.empty();
}

size_t PacketQueue::size() const{
    return queue_.size();
}