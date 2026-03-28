#include "business_layer/lobby/real_time_frame_cache.h"

RealTimeFrameCache::RealTimeFrameCache() {

}

void RealTimeFrameCache::onFrame(const KeyFrame& frameData) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto& entry = _cameraFrameMap[frameData.cameraId];

    if(frameData.timestamp <= entry.timestamp)
        return ;
    
    entry = frameData;

}


KeyFrame RealTimeFrameCache::getCameraRealTimeFrame( const CameraInfo& info) {
    auto it = _cameraFrameMap.find(info.getDeviceId());
    if(it == _cameraFrameMap.end() )
        return KeyFrame{};

    return it -> second;
}