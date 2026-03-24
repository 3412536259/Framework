#include "business_layer/stream/frame_dispater.h"

FrameDispater::FrameDispater() {

}

FrameDispater::~FrameDispater() {

}

bool FrameDispater::onKeyFrame(const FrameData& frame) {

}

void FrameDispater::addConsumer(const std::shared_ptr<IFrameConsumer> c) {
    std::lock_guard<std::mutex> lock(mutex_);
    consumers_.push_back(c); 
}

void FrameDispater::dispaterKeyFrame(const FrameData& frame) {
    std::lock_guard<std::mutex> lock(mutex_);

    for(auto it = consumers_.begin(); it != consumers_.end();) {
        if(auto consumer = it -> lock()) {
            consumer -> onFrame(frame);
            ++ it;
        }else it = consumers_.erase(it);
    }
}