#ifndef PLC_WATER_LEVEL_SENSOR_STATUS_H
#define PLC_WATER_LEVEL_SENSOR_STATUS_H

#include "data_layer/device/device_status.h"
#include "data_layer/sensor/sensor_types.h"
class PlcWaterLevelSensorStatus : public DeviceStatus {

    public:
        PlcWaterLevelSensorStatus() = default;
        PlcWaterLevelSensorStatus(const std::string& deviceId,
                                  const int type,
                                  const std::string& name,
                                  const WaterLevelSensorStatus& status);
        ~PlcWaterLevelSensorStatus() override = default;
    
    private:
        WaterLevelSensorStatus status_;
};

#endif