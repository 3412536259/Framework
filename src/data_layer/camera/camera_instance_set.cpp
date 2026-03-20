#include "data_layer/camera/camera_instance_set.h"

CameraInstanceSet::CameraInstanceSet(std::unordered_map<std::string, std::unique_ptr<Camera> >&& cameras) 
{
    // for(auto& [key, cam] : cameras) {
    //     cameras_[key] = std::move(cam);
    // }
    cameras_= std::move(cameras);
}

CameraInstanceSet::~CameraInstanceSet() {

}

std::vector<CameraStatus> CameraInstanceSet::getCameraStatusList()  {
    std::vector<CameraStatus> cameraStatusList;
    cameraStatusList.reserve(cameras_.size());
    for(auto& [key,camera] : cameras_) {
        cameraStatusList.push_back(camera -> getStatus());
    }
    return cameraStatusList;
}

CameraHistoryVideo CameraInstanceSet::getCameraHistoryVideo(const std::string& cameraId) {
    auto camera = cameras_.find(cameraId);
    if(camera == cameras_.end()) {
        return CameraHistoryVideo();
    }
    return camera->second->getCameraHistoryVideo(); 
}

std::vector<std::unique_ptr<DeviceData> > CameraInstanceSet::acquisitionCameraData() {
    std::vector<std::unique_ptr<DeviceData> > cameraDataList;
    cameraDataList.reserve(cameras_.size());
    for(auto& [cameraId, camera] : cameras_) {
        CameraStatus status = camera->getStatus();
        cameraDataList.push_back(std::make_unique<DeviceData>(2, status));
    }
    return cameraDataList;
}