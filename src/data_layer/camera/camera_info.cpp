#include "camera_info.h"

CameraInfo::CameraInfo() {

}

CameraInfo::CameraInfo(std::string deviceId) : deviceId_(deviceId) {

}

CameraInfo::~CameraInfo() {

}

const std::string CameraInfo::getDeviceId() const {
    return deviceId_;
}