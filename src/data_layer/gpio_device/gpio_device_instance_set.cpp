#include "data_layer/gpio_device/gpio_device_instance_set.h"

#include <iostream>
GPIODeviceInstanceSet::GPIODeviceInstanceSet() {
    

    auto& config = ConfigParser::getInstance().getConfig();
    for(auto& lock : config.doorLocks) {
        DoorLock dl = DoorLock(3,lock.id,lock.name,lock.pin,lock.direction);
        doorLocks_.emplace(lock.id,dl);
    }

    for(auto& smoke : config.smokeDetectors) {
        SmokeDetector sd = SmokeDetector(5,smoke.id,smoke.name,smoke.pin,smoke.direction);
        smokeDetectors_.emplace(smoke.id,sd);
    }

    for(auto& infrared : config.infraredSensors) {
        InfraredSensor is = InfraredSensor(4,infrared.id,infrared.name,infrared.pin,infrared.direction);
        infraredSensors_.emplace(infrared.id,is);
    }

    for(auto& water : config.waterLevelSensors) {
        WaterLevelSensor wls = WaterLevelSensor(6,water.id,water.name,water.pin,water.direction);
        waterLevelSensors_.emplace(water.id,wls);
    }
}

bool GPIODeviceInstanceSet::lockDoorLock(const GPIODeviceSimpleInfo& info) {
    auto it = doorLocks_.find(info.getDeviceId());

    if(it == doorLocks_.end())
        return false;

    DoorLock& lock = it -> second;

    return lock.lockDoorLock();
}
bool GPIODeviceInstanceSet::unlockDoorLock(const GPIODeviceSimpleInfo& info) {
    auto it = doorLocks_.find(info.getDeviceId());

    if(it == doorLocks_.end())
        return false;

    DoorLock& lock = it -> second;

    return lock.unlockDoorLock();
}

std::vector<DoorLockStatus> GPIODeviceInstanceSet::getDoorLockStatusList() {
    std::vector<DoorLockStatus> doorLockStatusList;
    doorLockStatusList.reserve(doorLocks_.size());
    for(auto& [key,lock] : doorLocks_) {
        doorLockStatusList.push_back(lock.queryDoorLockStatus());
    }
    return doorLockStatusList;
}

std::vector<SmokeDetectorStatus> GPIODeviceInstanceSet::getSmokeDetectorStatusList() {
    std::vector<SmokeDetectorStatus> smokeStatusList;
    smokeStatusList.reserve(smokeDetectors_.size());
    for(auto& [key,detector] : smokeDetectors_) {
        smokeStatusList.push_back(detector.queryStatus());
    }
    return smokeStatusList;
}
std::vector<WaterLevelSensorStatus> GPIODeviceInstanceSet::getWaterLevelSensorStatusList() {
    std::vector<WaterLevelSensorStatus> waterLevelStatusList;
    waterLevelStatusList.reserve(waterLevelSensors_.size());
    for(auto& [key,sensor] : waterLevelSensors_) {
        waterLevelStatusList.push_back(sensor.queryStatus());
    }
    return waterLevelStatusList;
}
std::vector<InfraredSensorStatus> GPIODeviceInstanceSet::getInfraredSensorStatusList() {
    std::vector<InfraredSensorStatus> sensorStatusList;
    sensorStatusList.reserve(infraredSensors_.size());
    for(auto& [key,sensor] : infraredSensors_) {
        sensorStatusList.push_back(sensor.queryStatus());
    }
    return sensorStatusList;
}

SmokeDetectorStatus GPIODeviceInstanceSet::getSmokeDetectorStatus(const std::string& deviceId) {
    auto it = smokeDetectors_.find(deviceId);

    if(it == smokeDetectors_.end()){
        return SmokeDetectorStatus();
    }

    return it->second.queryStatus();
}
WaterLevelSensorStatus GPIODeviceInstanceSet::getWaterLevelSensorStatus(const std::string& deviceId) {
    auto it = waterLevelSensors_.find(deviceId);

    if(it == waterLevelSensors_.end()){
        return WaterLevelSensorStatus();
    }

    return it->second.queryStatus();
}
InfraredSensorStatus GPIODeviceInstanceSet::getInfraredSensorStatus(const std::string& deviceId) {
    auto it = infraredSensors_.find(deviceId);

    if(it == infraredSensors_.end()){
        return InfraredSensorStatus();
    }

    return it->second.queryStatus();
}

std::vector<DeviceData> GPIODeviceInstanceSet::acquisitionDoorLockData() {
    std::vector<DeviceData> doorLockDataList;
    doorLockDataList.reserve(doorLocks_.size());

    for(auto& [key, doorLock] : doorLocks_) {
        DoorLockStatus status = doorLock.queryDoorLockStatus();
        doorLockDataList.push_back( DeviceData(3,status) );
    }

    return doorLockDataList;
}

std::vector<DeviceData> GPIODeviceInstanceSet::acquisitionInfraredSensorData() {
    std::vector<DeviceData> infraredSensorDataList;
    infraredSensorDataList.reserve(infraredSensors_.size());

    for(auto& [key, sensor] : infraredSensors_) {
        InfraredSensorStatus status = sensor.queryStatus();
        infraredSensorDataList.push_back( DeviceData(4,status) );
    }

    return infraredSensorDataList;
}

std::vector<DeviceData> GPIODeviceInstanceSet::acquisitionSmokeDetectorData() {
    std::vector<DeviceData> smokeDetectorDataList;
    smokeDetectorDataList.reserve(smokeDetectors_.size());

    for(auto& [key, detector] : smokeDetectors_) {
        SmokeDetectorStatus status = detector.queryStatus();
        smokeDetectorDataList.push_back( DeviceData(5,status) );
    }

    return smokeDetectorDataList;
}

std::vector<DeviceData> GPIODeviceInstanceSet::acquisitionWaterLevelSensorData() {
    std::vector<DeviceData> waterLevelSensorDataList;
    waterLevelSensorDataList.reserve(waterLevelSensors_.size());

    for(auto& [key, sensor] : waterLevelSensors_) {
        WaterLevelSensorStatus status = sensor.queryStatus();
        waterLevelSensorDataList.push_back( DeviceData(6,status) );
    }

    return waterLevelSensorDataList;
}