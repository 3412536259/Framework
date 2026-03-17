#ifndef PLC_SMOKE_DETECTOR_STATUS_H
#define PLC_SMOKE_DETECTOR_STATUS_H

#include "device_status.h"
#include "sensor_types.h"
class PlcSmokeDetectorStatus : public DeviceStatus {

    public:
        PlcSmokeDetectorStatus() = default;
        PlcSmokeDetectorStatus(const std::string& deviceId,
                               const int type,
                               const std::string& name,
                               const SmokeDetectorStatus& status);
        ~PlcSmokeDetectorStatus() override = default;
    
    private:
        SmokeDetectorStatus status_;
};

#endif