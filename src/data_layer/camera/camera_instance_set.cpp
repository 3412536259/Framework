#include "data_layer/camera/camera_instance_set.h"

CameraInstanceSet::CameraInstanceSet(const std::unordered_map<std::string, std::unique_ptr<Camera> >& cameras) 
    : cameras_(cameras) 
{

}

CameraInstanceSet::~CameraInstanceSet() {

}

std::vector<CameraStatus> CameraInstanceSet::getCameraStatusList() const {
    std::vector<CameraStatus> cameraStatusList;
    cameraStatusList.reserve(cameras_.size());
    for(const auto& [key,camera] : cameras_) {
        cameraStatusList.push_back( camera->getStatus());
    }
    return cameraStatusList;
}

CameraHistoryVideo CameraInstanceSet::getCameraHistoryVideo(const std::string& cameraId) const {
    auto camera = cameras_.find(cameraId);
    if(camera == cameras_.end()) {
        return CameraHistoryVideo();
    }
    return camera->second->getCameraHistoryVideo(); 
}

std::vector<std::unique_ptr<DeviceData> > CameraInstanceSet::acquisitionCameraData() {
    std::vector<std::unique_ptr<DeviceData> > cameraDataList;
    cameraDataList.reserve(cameras_.size());
    for(const auto& [cameraId, camera] : cameras_) {
        CameraStatus status = camera->getStatus();
        cameraDataList.push_back(std::make_unique<DeviceData>(2, status));
    }
    return cameraDataList;
}