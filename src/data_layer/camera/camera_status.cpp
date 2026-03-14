#include "camera_status.h"

CameraStatus::CameraStatus(const std::string& deviceId,
                           const int type,
                           const std::string& name,
                           const Status& status)
    : DeviceStatus(deviceId,type,name),
      status_(status) {

}


// Status CameraStatus::getStatus() const{
//     return status_;
// }

// const CameraStatus& CameraStatus::getCameraStatus() const {
//     return *this;
// }