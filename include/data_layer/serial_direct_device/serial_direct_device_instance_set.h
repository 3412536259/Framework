#ifndef SERIAL_DIRECT_DEVICE_INSTANCE_SET_H
#define SERIAL_DIRECT_DEVICE_INSTANCE_SET_H

#include <vector>
#include <unordered_map>
#include "data_layer/sensor/temp_humid_sensor.h"
#include "data_layer/sensor/temp_humid_sensor_status.h"
#include "data_layer/device/device_data.h"
#include "common/config/config_parser.h"
class SerialDirectDeviceInstanceSet {

    public:
        ~SerialDirectDeviceInstanceSet() = default;
        SerialDirectDeviceInstanceSet();

        std::vector<TempHumidSensorStatus> getSensorStatusList();

        TempHumidSensorStatus getSensorStatus(const std::string& deviceId);

        std::vector<DeviceData> acquisitionTempHumidSensorData();
    
    private:
        std::unordered_map<std::string, TempHumidSensor>  sensors_;
};

#endif