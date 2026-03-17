#ifndef SENSOR_STATUS_H
#define SENSOR_STATUS_H

#include <string>
#include "sensor_types.h"
#include "device_status.h"

class SensorStatus : DeviceStatus{
    public:
        SensorStatus() = default;
        SensorStatus(const std::string& deviceId,
                     const int type,
                     const std::string& name,
                     const Status& status,
                     float humidity,
                     float tempature);
        ~SensorStatus() override = default;
    
    private:

        Status status_;
        float humidity_;
        float tempature_;


};

#endif