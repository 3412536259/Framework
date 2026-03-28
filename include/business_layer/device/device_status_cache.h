#pragma once

#include "data_layer/box/box_device_status.h"
#include "data_layer/plc_device/solenoid_status.h"
#include "data_layer/sensor/temp_humid_sensor_status.h"
#include "data_layer/gpio_device/door_lock_status.h"
#include "data_layer/plc_device/plc_device_info.h"
#include "data_layer/gpio_device/gpio_device_simple_info.h"
#include "data_layer/device/device_data.h"

#include<unordered_map>
#include<memory>
#include<vector>

class DeviceStatusCache {

    public:

        DeviceStatusCache();
        ~DeviceStatusCache();

        void updateBoxDeviceStatus( const BoxDeviceStatus& devices);
        void updateDeviceStatus( const std::vector<DeviceData>& deviceDataList );

        BoxDeviceStatus getBoxDeviceStatus();

        SolenoidStatus getSolenoidValueStatus(const std::string& deviceId);
        TempHumidSensorStatus getTempHumidSensorStatus(const std::string& deviceId);
        InfraredSensorStatus getInfraredSensorStatus(const std::string& deviceId);
        SmokeDetectorStatus getSmokeDetectorStatus(const std::string& deviceId);
        WaterLevelSensorStatus getWaterLevelSensorStatus(const std::string& deviceId);

        bool findSolenoidStatus(const std::string& deviceId);
        bool findTempHumidSensorStatus(const std::string& deviceId);
        bool findInfraredSensorStatus(const std::string& deviceId);
        bool findSmokeDetectorStatus(const std::string& deviceId);
        bool findWaterLevelSensorStatus(const std::string& deviceId);

        bool isBoxDeviceStatusEmpty();

        bool isSolenoidOpen( const PlcDeviceInfo& info);
        bool isSolenoidClose( const PlcDeviceInfo& info);
        bool isDoorLockLock(const GPIODeviceSimpleInfo& info);

        void updateSolenoidStatus( const SolenoidStatus& status);
        void updateTempHumidSensorStatus( const TempHumidSensorStatus& status);
        void updateInfraredSensorStatus(const InfraredSensorStatus& status);
        void updateWaterLevelSensorStatus(const WaterLevelSensorStatus& status);
        void updateSmokeDetectorStatus(const SmokeDetectorStatus& status);
        void updateDoorLockStatus(const DoorLockStatus& status);

    private:
        std::unordered_map<std::string, SolenoidStatus> solenoidStatusMap_;
        std::unordered_map<std::string, TempHumidSensorStatus> sensorStatusMap_;
        std::unordered_map<std::string, InfraredSensorStatus> infraredSensorStatusMap_;
        std::unordered_map<std::string, WaterLevelSensorStatus> waterLevelSensorStatusMap_;
        std::unordered_map<std::string, SmokeDetectorStatus> smokeDetectorStatusMap_;
        std::unordered_map<std::string, DoorLockStatus> doorLockStatusMap_;
        // std::unordered_map<std::string, std::unique_ptr<RadarStatus> > _radarStatusMap;
        // std::unordered_map<std::string, std::unique_ptr<CarStatus> > _carStatusMap;

};

