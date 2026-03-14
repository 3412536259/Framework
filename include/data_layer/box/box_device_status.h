#ifndef BOX_DEVICE_STATUS_H
#define BOX_DEVICE_STATUS_H

#include "solenoid_status.h"
#include "sensor_status.h"
#include "camera_status.h"
#include<vector>

class BoxDeviceStatus {
    public:
        BoxDeviceStatus(const std::vector<SolenoidStatus>& solenoidStatuses,
                        const std::vector<CameraStatus>& cameraStatuses,
                        const std::vector<SensorStatus>& sensorStatuses);
        BoxDeviceStatus() = default;
        ~BoxDeviceStatus() = default;

        std::vector<SolenoidStatus> getSolenoidStatusList() const ;
        std::vector<SensorStatus> getSensorStatusList() const;
        std::vector<CameraStatus> getCameraStatusList() const;

    private:
        std::vector<SolenoidStatus> solenoidStatuses_;
        std::vector<SensorStatus> sensorStatuses_;
        std::vector<CameraStatus> cameraStatuses_;

};

#endif