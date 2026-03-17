#ifndef CAMERA_STATUS_H
#define CAMERA_STATUS_H

#include <string>
#include  "camera_utils.h"
#include "device_status.h"
class CameraStatus : public DeviceStatus{
    public:
        CameraStatus(const std::string& deviceId,
                     const int type,
                     const std::string& name,
                     const Status& status);
        CameraStatus() = default;
        ~CameraStatus() override = default;
        // Status getStatus() const;
        // const CameraStatus& getCameraStatus() const;

    private:

        Status status_;

};

#endif 