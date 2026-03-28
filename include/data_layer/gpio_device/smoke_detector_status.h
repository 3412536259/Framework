#ifndef SMOKE_DETECTOR_STATUS_H
#define SMOKE_DETECTOR_STATUS_H

#include "data_layer/device/device_status.h"
#include "data_layer/sensor/sensor_types.h"
class SmokeDetectorStatus : public DeviceStatus {

    public:
        SmokeDetectorStatus() = default;
        SmokeDetectorStatus(const std::string& deviceId,
                               const int type,
                               const std::string& name,
                               const SmokeStatus& status);
        ~SmokeDetectorStatus() override = default;

        std::string getStatus();
    
    private:
        SmokeStatus status_;
};

#endif