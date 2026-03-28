#ifndef BOX_DEVICE_STATUS_H
#define BOX_DEVICE_STATUS_H

#include "data_layer/plc_device/solenoid_status.h"
#include "data_layer/sensor/temp_humid_sensor_status.h"
#include "data_layer/camera/camera_status.h"
#include "data_layer/gpio_device/door_lock_status.h"
#include "data_layer/gpio_device/infrared_sensor_status.h"
#include "data_layer/gpio_device/smoke_detector_status.h"
#include "data_layer/gpio_device/water_level_sensor_status.h"
#include "data_layer/gpio_device/door_lock_status.h"
#include<vector>

class BoxDeviceStatus {
    public:
        BoxDeviceStatus(const std::vector<SolenoidStatus> solenoidStatuses,
                        const std::vector<TempHumidSensorStatus> sensorStatuses,
                        const std::vector<InfraredSensorStatus> infraredSensorStatuses,
                        const std::vector<SmokeDetectorStatus> smokeDetectorStatuses,
                        const std::vector<WaterLevelSensorStatus> waterSensorStatuses,
                        const std::vector<DoorLockStatus> doorLockStatuses);
        BoxDeviceStatus() = default;
        ~BoxDeviceStatus() = default;

        std::vector<SolenoidStatus> getSolenoidStatusList() const ;
        std::vector<TempHumidSensorStatus> getSensorStatusList() const;
        std::vector<InfraredSensorStatus> getInfraredSensorStatusList() const;
        std::vector<SmokeDetectorStatus> getSmokeDetectorStatusList() const;
        std::vector<WaterLevelSensorStatus> getWaterLevelSensorStatusList() const;
        std::vector<DoorLockStatus> getDoorLockStatusList() const;
            
    private:
        std::vector<SolenoidStatus> solenoidStatuses_;
        std::vector<TempHumidSensorStatus> sensorStatuses_;
        std::vector<InfraredSensorStatus> infraredSensorStatuses_;
        std::vector<SmokeDetectorStatus> smokeDetectorStatuses_;
        std::vector<WaterLevelSensorStatus> waterSensorStatuses_;
        std::vector<DoorLockStatus> doorLockStatuses_;

};

#endif