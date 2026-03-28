#include "business_layer/device/device_status_cache.h"

#include <iostream>
#include <functional>
DeviceStatusCache::DeviceStatusCache() {
    solenoidStatusMap_.clear(); 
    solenoidStatusMap_.reserve(16);
    sensorStatusMap_.clear();   
    sensorStatusMap_.reserve(8);
    infraredSensorStatusMap_.clear(); 
    infraredSensorStatusMap_.reserve(4);
    waterLevelSensorStatusMap_.clear(); 
    waterLevelSensorStatusMap_.reserve(4);
    smokeDetectorStatusMap_.clear(); 
    smokeDetectorStatusMap_.reserve(4);
    doorLockStatusMap_.clear(); 
    doorLockStatusMap_.reserve(4);
}

DeviceStatusCache::~DeviceStatusCache() {

}

void DeviceStatusCache::updateBoxDeviceStatus( const BoxDeviceStatus& devices) {
    const std::vector<SolenoidStatus>& solenoidStatusList = devices.getSolenoidStatusList();
    for( auto& solenoidStatus : solenoidStatusList) {
        updateSolenoidStatus(solenoidStatus);
    }

    const std::vector<TempHumidSensorStatus> sensorStatusList = devices.getSensorStatusList();
    for( auto& sensorStatus : sensorStatusList) {
        updateTempHumidSensorStatus(sensorStatus);
    }

    const std::vector<InfraredSensorStatus>& infraredSensorStatusList = devices.getInfraredSensorStatusList();
    for( auto& infraredSensorStatus : infraredSensorStatusList) {
        updateInfraredSensorStatus(infraredSensorStatus);
    }

    const std::vector<WaterLevelSensorStatus>& waterLevelSensorStatusList = devices.getWaterLevelSensorStatusList();
    for( auto& sensorStatus : waterLevelSensorStatusList) {
        updateWaterLevelSensorStatus(sensorStatus);
    }

    const std::vector<SmokeDetectorStatus>& smokeDetectorStatusList = devices.getSmokeDetectorStatusList();
    for( auto& status : smokeDetectorStatusList) {
        updateSmokeDetectorStatus(status);
    }

    const std::vector<DoorLockStatus>& doorLockStatusList = devices.getDoorLockStatusList();
    for( auto& status : doorLockStatusList) {
        updateDoorLockStatus(status);
    }
}

void DeviceStatusCache::updateDeviceStatus( const std::vector<DeviceData>& deviceDataList ) {
    if(deviceDataList.empty() ) return ;

    const DeviceData& deviceData = deviceDataList.front();

    switch(deviceData.getType()) {
        case 0:
            for(auto& solenoid : deviceDataList)
                updateSolenoidStatus( solenoid.getSolenoidStatus()); 
            break;
        case 1: 
            for(auto& sensor : deviceDataList)
                updateTempHumidSensorStatus(sensor.getSensorStatus());
            break;
        case 3:
            for(auto& doorLock : deviceDataList)
                updateDoorLockStatus(doorLock.getDoorLockStatus());
            break;
        case 4:
            for(auto& infraredSensor : deviceDataList)
                updateInfraredSensorStatus(infraredSensor.getInfraredSensorStatus());
            break;
        case 5:
            for(auto& smokeDetector : deviceDataList)
                updateSmokeDetectorStatus(smokeDetector.getSmokeDetectorStatus());
            break;
        case 6:
            for(auto& waterLevelSensor : deviceDataList)
                updateWaterLevelSensorStatus(waterLevelSensor.getWaterLevelSensorStatus());
            break;
        default:
            break;
    }

}


BoxDeviceStatus DeviceStatusCache::getBoxDeviceStatus() {
    std::vector<SolenoidStatus> solenoidStatusList;
    solenoidStatusList.reserve(solenoidStatusMap_.size());
    for( auto& [id, solenoid] : solenoidStatusMap_) {
        solenoidStatusList.push_back(solenoid );
    }

    std::vector<TempHumidSensorStatus> sensorStatusList;
    for( auto& [id, sensor] : sensorStatusMap_) {
        sensorStatusList.push_back( sensor );
    }

    std::vector<DoorLockStatus> doorLockStatusList;
    for( auto& [id, doorLock] : doorLockStatusMap_) {
        doorLockStatusList.push_back( doorLock );
    }

    std::vector<InfraredSensorStatus> infraredSensorStatusList;
    for( auto& [id, sensor] : infraredSensorStatusMap_) {
        infraredSensorStatusList.push_back( sensor );
    }

    std::vector<SmokeDetectorStatus> smokeDetectorStatusList;
    for( auto& [id, detector] : smokeDetectorStatusMap_) {
        smokeDetectorStatusList.push_back( detector );
    }

    std::vector<WaterLevelSensorStatus> waterLevelStatusList;
    for( auto& [id, sensor] : waterLevelSensorStatusMap_) {
        waterLevelStatusList.push_back( sensor );
    }

    return BoxDeviceStatus(solenoidStatusList, sensorStatusList,
                           infraredSensorStatusList,smokeDetectorStatusList,waterLevelStatusList,doorLockStatusList);
}

SolenoidStatus DeviceStatusCache::getSolenoidValueStatus(const std::string& deviceId) {
    auto it = solenoidStatusMap_.find(deviceId);

    if(it == solenoidStatusMap_.end())
        return SolenoidStatus();
    return it -> second;
}
TempHumidSensorStatus DeviceStatusCache::getTempHumidSensorStatus(const std::string& deviceId) {
    auto it  = sensorStatusMap_.find(deviceId);

    if(it == sensorStatusMap_.end())
        return TempHumidSensorStatus();
    return it -> second;
}
InfraredSensorStatus DeviceStatusCache::getInfraredSensorStatus(const std::string& deviceId) {
    auto it = infraredSensorStatusMap_.find(deviceId);

    if(it == infraredSensorStatusMap_.end())
        return InfraredSensorStatus();
    return it -> second;
}
SmokeDetectorStatus DeviceStatusCache::getSmokeDetectorStatus(const std::string& deviceId) {
    auto it = smokeDetectorStatusMap_.find(deviceId);

    if(it == smokeDetectorStatusMap_.end())
        return SmokeDetectorStatus();
    return it -> second;
}
WaterLevelSensorStatus DeviceStatusCache::getWaterLevelSensorStatus(const std::string& deviceId) {
    auto it = waterLevelSensorStatusMap_.find(deviceId);

    if(it == waterLevelSensorStatusMap_.end())
        return WaterLevelSensorStatus();
    return it -> second;
}

bool DeviceStatusCache::findSolenoidStatus(const std::string& deviceId) {
    auto it = solenoidStatusMap_.find(deviceId);

    if(it == solenoidStatusMap_.end())
        return false;
    return true;
}
bool DeviceStatusCache::findTempHumidSensorStatus(const std::string& deviceId) {
    auto it = sensorStatusMap_.find(deviceId);

    if(it == sensorStatusMap_.end())
        return false;
    return true;
}
bool DeviceStatusCache::findInfraredSensorStatus(const std::string& deviceId) {
    auto it = infraredSensorStatusMap_.find(deviceId);

    if(it == infraredSensorStatusMap_.end())
        return false;
    return true;
}
bool DeviceStatusCache::findSmokeDetectorStatus(const std::string& deviceId) {
    auto it = smokeDetectorStatusMap_.find(deviceId);

    if(it == smokeDetectorStatusMap_.end())
        return false;
    return true;
}
bool DeviceStatusCache::findWaterLevelSensorStatus(const std::string& deviceId) {
    auto it = waterLevelSensorStatusMap_.find(deviceId);

    if(it == waterLevelSensorStatusMap_.end())
        return false;
    return true;
}

bool DeviceStatusCache::isBoxDeviceStatusEmpty() {
    return solenoidStatusMap_.empty() && sensorStatusMap_.empty();
}


bool DeviceStatusCache::isSolenoidOpen( const PlcDeviceInfo& info) {
    auto it = solenoidStatusMap_.find(info.getDeviceId());

    if(it == solenoidStatusMap_.end())
        throw std::runtime_error("Solenoid device not found in cache");

    SolenoidStatus& status = it->second;
    return status.isOpen();
}

bool DeviceStatusCache::isSolenoidClose( const PlcDeviceInfo& info) {
    auto it = solenoidStatusMap_.find(info.getDeviceId());

    if(it == solenoidStatusMap_.end())
        throw std::runtime_error("Solenoid device not found in cache");

    SolenoidStatus& status = it->second;
    return !status.isOpen();
}

bool DeviceStatusCache::isDoorLockLock(const GPIODeviceSimpleInfo& info) {
    auto it = doorLockStatusMap_.find(info.getDeviceId());

    if(it == doorLockStatusMap_.end()) {
        std::cout << "没有门锁状态缓存" << std::endl;
        return 0;
    }
    std::cout << "是否执行" << std::endl;
    DoorLockStatus& status = it->second;
    return status.isLock();
}

void DeviceStatusCache::updateSolenoidStatus( const SolenoidStatus& status ) {
    const std::string& deviceId = status.getDeviceId();

    auto it = solenoidStatusMap_.find(deviceId);
    if(it == solenoidStatusMap_.end()) 
        solenoidStatusMap_[deviceId] = status;
    else it->second = status;
}

void DeviceStatusCache::updateTempHumidSensorStatus( const TempHumidSensorStatus& status) {

    const std::string& deviceId = status.getDeviceId();
    auto it = sensorStatusMap_.find(deviceId);
    if(it == sensorStatusMap_.end())
        sensorStatusMap_[deviceId] = status;
    else it->second = status;
}

void DeviceStatusCache::updateInfraredSensorStatus(const InfraredSensorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = infraredSensorStatusMap_.find(deviceId);
    if(it == infraredSensorStatusMap_.end())
        infraredSensorStatusMap_[deviceId] = status;
    else it->second = status;
 }
void DeviceStatusCache::updateWaterLevelSensorStatus(const WaterLevelSensorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = waterLevelSensorStatusMap_.find(deviceId);
    if(it == waterLevelSensorStatusMap_.end())
        waterLevelSensorStatusMap_[deviceId] = status;
    else it->second = status;
}
void DeviceStatusCache::updateSmokeDetectorStatus(const SmokeDetectorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = smokeDetectorStatusMap_.find(deviceId);
    if(it == smokeDetectorStatusMap_.end())
        smokeDetectorStatusMap_[deviceId] = status;
    else it->second = status;
}
void DeviceStatusCache::updateDoorLockStatus(const DoorLockStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = doorLockStatusMap_.find(deviceId);
    if(it == doorLockStatusMap_.end())
        doorLockStatusMap_[deviceId] = status;
    else it->second = status;
}
