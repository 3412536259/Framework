#include "camera.h"

Camera::Camera(std::string cameraId, std::string name, std::string rtspUrl) 
    : cameraId_(cameraId), name_(name), rtspUrl_(rtspUrl), onlineStatus_(Status::OFFLINE) 
{
    std::lock_guard<std::mutex> lock(sattusMutex_);
    onlineStatus_ = Status::OFFLINE;
}

Camera::~Camera() {
    
}

bool Camera::start() {

}

bool Camera::stop() {

}

bool Camera::isRunning() const {

}

bool Camera::getLastKeyFrame(FrameData& out) {

}

CameraHistoryVideo Camera::getCameraHistoryVideo() {
    
}

CameraStatus Camera::getStatus() {

}

void Camera::pullKeyFrameLoop() {

}