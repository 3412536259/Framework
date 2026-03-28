#include "business_layer/stream/frame_dispater.h"

FrameDispater::FrameDispater() {

}

FrameDispater::~FrameDispater() {
    std::lock_guard<std::mutex> lock(mutex_);
    consumers_.clear();
}

bool FrameDispater::onKeyFrame(const AVFrame* frame) {
    if(!frame)
        return false;
    
    if(frame -> key_frame == 1)
        return true;
    
    if(frame -> pict_type == AV_PICTURE_TYPE_I)
        return true;

    return false;
}

void FrameDispater::addConsumer(const std::shared_ptr<IFrameConsumer> c) {
    std::lock_guard<std::mutex> lock(mutex_);
    consumers_.push_back(c); 
}

void FrameDispater::dispaterKeyFrame(const KeyFrame& frame) {
    std::lock_guard<std::mutex> lock(mutex_);

    for(auto it = consumers_.begin(); it != consumers_.end();) {
        if(auto consumer = it -> lock()) {
            consumer -> onFrame(frame);
            ++ it;
        }else it = consumers_.erase(it);
    }
}