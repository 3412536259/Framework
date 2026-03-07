#ifndef CAMERA_STATUS_H
#define CAMERA_STATUS_H

#include  "camera_utils.h"

#include <string>
class CameraStatus {
    public:
        CameraStatus();
        ~CameraStatus();

    private:
        std::string deviceId;

        Status status;

};

#endif 