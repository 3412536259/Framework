#include "real_time_frame_cache.h"

RealTimeFrameCache::RealTimeFrameCache() {

}

RealTimeFrameCache::~RealTimeFrameCache() {

}

void RealTimeFrameCache::updateCameraRealTimeFrame() {

}

CameraRealTimeFrame RealTimeFrameCache::getCameraRealTimeFrame( const CameraInfo& info) {
    auto it = _cameraFrameMap.find(info.getCameraId());
    if(it == _cameraFrameMap.end() )
        return new CameraRealTimeFrame();

    return it -> sencond;
}