#ifndef GPIO_DEVICE_INSTANCE_SET_H
#define GPIO_DEVICE_INSTANCE_SET_H

#include <vector>
#include <unordered_map>
#include "data_layer/gpio_device/door_lock_status.h"
#include "data_layer/gpio_device/gpio_device_simple_info.h"
#include "data_layer/gpio_device/door_lock.h"
#include "data_layer/gpio_device/smoke_detector.h"
#include "data_layer/gpio_device/smoke_detector_status.h"
#include "data_layer/gpio_device/infrared_sensor.h"
#include "data_layer/gpio_device/infrared_sensor_status.h"
#include "data_layer/gpio_device/water_level_sensor.h"
#include "data_layer/gpio_device/water_level_sensor_status.h"
#include "data_layer/device/device_data.h"
#include "common/config/config_parser.h"
class GPIODeviceInstanceSet {

    public:
        GPIODeviceInstanceSet();
        ~GPIODeviceInstanceSet() = default;

        bool lockDoorLock(const GPIODeviceSimpleInfo& info);
        bool unlockDoorLock(const GPIODeviceSimpleInfo& info);

        std::vector<DoorLockStatus> getDoorLockStatusList();
        std::vector<SmokeDetectorStatus> getSmokeDetectorStatusList();
        std::vector<WaterLevelSensorStatus> getWaterLevelSensorStatusList();
        std::vector<InfraredSensorStatus> getInfraredSensorStatusList();

        SmokeDetectorStatus getSmokeDetectorStatus(const std::string& deviceId);
        WaterLevelSensorStatus getWaterLevelSensorStatus(const std::string& deviceId);
        InfraredSensorStatus getInfraredSensorStatus(const std::string& deviceId);

        std::vector<DeviceData> acquisitionDoorLockData();
        std::vector<DeviceData> acquisitionInfraredSensorData();
        std::vector<DeviceData> acquisitionSmokeDetectorData();
        std::vector<DeviceData> acquisitionWaterLevelSensorData();
    
    private:
        std::unordered_map<std::string, DoorLock> doorLocks_;
        std::unordered_map<std::string, SmokeDetector> smokeDetectors_;
        std::unordered_map<std::string, InfraredSensor> infraredSensors_;
        std::unordered_map<std::string, WaterLevelSensor> waterLevelSensors_;

};

#endif