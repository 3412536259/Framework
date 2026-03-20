#pragma once

#include "data_layer/box/box_device_status.h"
#include "data_layer/plc_device/solenoid_status.h"
#include "data_layer/sensor/temp_humid_sensor_status.h"
#include "data_layer/camera/camera_status.h"
#include "data_layer/plc_device/infrared_sensor_status.h"
#include "data_layer/plc_device/plc_water_level_sensor_status.h"
#include "data_layer/plc_device/plc_smoke_detector_status.h"
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
        void updateDeviceStatus( const std::vector<std::unique_ptr<DeviceData> >& deviceDataList );

        BoxDeviceStatus getBoxDeviceStatus();

        bool isBoxDeviceStatusEmpty();

        bool isSolenoidOpen( const PlcDeviceInfo& info);
        bool isSolenoidClose( const PlcDeviceInfo& info);
        bool isDoorLockLock(const GPIODeviceSimpleInfo& info);

    private:
        void updateSolenoidStatus( const SolenoidStatus& status);
        void updateTempHumidSensorStatus( const TempHumidSensorStatus& status);
        void updateCameraStatus( const CameraStatus& status);
        void updateInfraredSensorStatus(const InfraredSensorStatus& status);
        void updatePlcWaterLevelSensorStatus(const PlcWaterLevelSensorStatus& status);
        void updatePlcSmokeDetectorStatus(const PlcSmokeDetectorStatus& status);
        void updateDoorLockStatus(const DoorLockStatus& status);

        std::unordered_map<std::string, std::unique_ptr<SolenoidStatus> > solenoidStatusMap_;
        std::unordered_map<std::string, std::unique_ptr<TempHumidSensorStatus> > sensorStatusMap_;
        std::unordered_map<std::string, std::unique_ptr<CameraStatus> > cameraStatusMap_;
        std::unordered_map<std::string, std::unique_ptr<InfraredSensorStatus> > infraredSensorStatusMap_;
        std::unordered_map<std::string, std::unique_ptr<PlcWaterLevelSensorStatus> > waterLevelSensorStatusMap_;
        std::unordered_map<std::string, std::unique_ptr<PlcSmokeDetectorStatus> > smokeDetectorStatusMap_;
        std::unordered_map<std::string, std::unique_ptr<DoorLockStatus> > doorLockStatusMap_;
        // std::unordered_map<std::string, std::unique_ptr<RadarStatus> > _radarStatusMap;
        // std::unordered_map<std::string, std::unique_ptr<CarStatus> > _carStatusMap;

};

