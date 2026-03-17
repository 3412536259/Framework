#pragma once

#include<unordered_map>
class RealTimeFrameCache {

    public:

        RealTimeFrameCache() ;
        ~RealTimeFrameCache() = default;
        void updateCameraRealTimeFrame();

        CameraRealTimeFrame getCameraRealTimeFrame( const CameraInfo& info);

    private:
        std::unordered_map<std::string, CameraRealTimeFrame> _cameraFrameMap;
};