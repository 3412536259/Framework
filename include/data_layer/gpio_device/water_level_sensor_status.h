#ifndef WATER_LEVEL_SENSOR_STATUS_H
#define WATER_LEVEL_SENSOR_STATUS_H

#include "data_layer/device/device_status.h"
#include "data_layer/sensor/sensor_types.h"
class WaterLevelSensorStatus : public DeviceStatus {

    public:
        WaterLevelSensorStatus() = default;
        WaterLevelSensorStatus(const std::string& deviceId,
                                  const int type,
                                  const std::string& name,
                                  const WaterLevelStatus& status);
        ~WaterLevelSensorStatus() override = default;

        std::string getStatus();
    
    private:
        WaterLevelStatus status_;
};

#endif