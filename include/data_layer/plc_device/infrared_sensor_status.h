#ifndef INFRARED_SENSOR_STATUS_H
#define INFRARED_SENSOR_STATUS_H

#include "device_status.h"
#include "sensor_types.h"
class InfraredSensorStatus : public DeviceStatus {

    public:
        InfraredSensorStatus() = default;
        InfraredSensorStatus(const std::string& deviceId,
                             const int type,
                             const std::string& name,
                             const InfraredStatus& status);
        ~InfraredSensorStatus() override = default;
    
    private:
        InfraredStatus status_;

};

#endif