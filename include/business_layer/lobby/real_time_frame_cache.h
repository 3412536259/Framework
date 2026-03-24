#pragma once

#include<unordered_map>
#include "data_layer/camera/camera_real_time_frame.h"
#include "data_layer/camera/camera_info.h"
#include "business_layer/stream/iframe_consumer.h"
class RealTimeFrameCache : public IFrameConsumer{

    public:

        RealTimeFrameCache() ;
        ~RealTimeFrameCache() = default;

        void onFrame(const Frame& frame) ;
        void updateCameraRealTimeFrame();

        CameraRealTimeFrame getCameraRealTimeFrame( const CameraInfo& info);

    private:
        std::unordered_map<std::string, CameraRealTimeFrame> _cameraFrameMap;
};