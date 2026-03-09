#ifndef BOX_DEVICE_STATUS_H
#define BOX_DEVICE_STATUS_H

#include "solenoid_status.h"
#include "sensor_status.h"
#include "camera_status.h"
#include<vector>

class BoxDeviceStatus {
    public:
        BoxDeviceStatus(std::vector<SolenoidStatus> SolenoidStatuses,
                        std::vector<CameraStatus> CameraStatuses,
                        std::vector<SensorStatus> SensorStatuses);
        BoxDeviceStatus() = default;
        ~BoxDeviceStatus();

    private:
        std::vector<SolenoidStatus> solenoidStatuses_;
        std::vector<SensorStatus> sensorStatuses_;
        std::vector<CameraStatus> cameraStatuses_;

};

#endif