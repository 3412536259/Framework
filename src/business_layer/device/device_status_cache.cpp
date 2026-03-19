#include "business_layer/device/device_status_cache.h"

#include <functional>
DeviceStatusCache::DeviceStatusCache() {

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
    const std::vector<CameraStatus>& cameraStatusList = devices.getCameraStatusList();
    for( auto& cameraStatus : cameraStatusList) {
        updateCameraStatus(cameraStatus);
    }

    const std::vector<InfraredSensorStatus>& infraredSensorStatusList = devices.getInfraredSensorStatusList();
    for( auto& infraredSensorStatus : infraredSensorStatusList) {
        updateInfraredSensorStatus(infraredSensorStatus);
    }

    const std::vector<PlcWaterLevelSensorStatus>& waterLevelSensorStatusList = devices.getWaterLevelSensorStatusList();
    for( auto& sensorStatus : waterLevelSensorStatusList) {
        updatePlcWaterLevelSensorStatus(sensorStatus);
    }

    const std::vector<PlcSmokeDetectorStatus>& smokeDetectorStatusList = devices.getSmokeDetectorStatusList();
    for( auto& status : smokeDetectorStatusList) {
        updatePlcSmokeDetectorStatus(status);
    }

    const std::vector<DoorLockStatus>& doorLockStatusList = devices.getDoorLockStatusList();
    for( auto& status : doorLockStatusList) {
        updateDoorLockStatus(status);
    }
}

void DeviceStatusCache::updateDeviceStatus( const std::vector<std::unique_ptr<DeviceData> >& deviceDataList ) {
    if(deviceDataList.empty() || !deviceDataList.front() ) return ;

    const DeviceData& deviceData = *deviceDataList.front();

    switch(deviceData.getType()) {
        case 0:
            for(auto& solenoidPtr : deviceDataList)
                updateSolenoidStatus( solenoidPtr -> getSolenoidStatus()); 
            break;
        case 1: 
            for(auto& sensorPtr : deviceDataList)
                updateTempHumidSensorStatus(sensorPtr -> getSensorStatus());
            break;
        case 2:
            for(auto& cameraPtr : deviceDataList)
                updateCameraStatus(cameraPtr -> getCameraStatus());
        case 3:
            for(auto& doorLockPtr : deviceDataList)
                updateDoorLockStatus(doorLockPtr -> getDoorLockStatus());
        case 4:
            for(auto& infraredSensorPtr : deviceDataList)
                updateInfraredSensorStatus(infraredSensorPtr -> getInfraredSensorStatus());
        case 5:
            for(auto& smokeDetectorPtr : deviceDataList)
                updatePlcSmokeDetectorStatus(smokeDetectorPtr -> getPlcSmokeDetectorStatus());
        case 6:
            for(auto& waterLevelSensorPtr : deviceDataList)
                updatePlcWaterLevelSensorStatus(waterLevelSensorPtr -> getPlcWaterLevelSensorStatus());
    }

}


BoxDeviceStatus DeviceStatusCache::getBoxDeviceStatus() {
    std::vector<SolenoidStatus> solenoidStatusList;
    solenoidStatusList.reserve(solenoidStatusMap_.size());
    for( auto& [id, ptr] : solenoidStatusMap_) {
        solenoidStatusList.push_back( *ptr );
    }

    std::vector<TempHumidSensorStatus> sensorStatusList;
    for( auto& [id, ptr] : sensorStatusMap_) {
        sensorStatusList.push_back( *ptr );
    }

    std::vector<CameraStatus> cameraStatusList;
    for( auto& [id, ptr] : cameraStatusMap_) {
        cameraStatusList.push_back( *ptr );
    }

    std::vector<DoorLockStatus> doorLockStatusList;
    for( auto& [id, ptr] : doorLockStatusMap_) {
        doorLockStatusList.push_back( *ptr );
    }

    std::vector<InfraredSensorStatus> infraredSensorStatusList;
    for( auto& [id, ptr] : infraredSensorStatusMap_) {
        infraredSensorStatusList.push_back( *ptr );
    }

    std::vector<PlcSmokeDetectorStatus> smokeDetectorStatusList;
    for( auto& [id, ptr] : smokeDetectorStatusMap_) {
        smokeDetectorStatusList.push_back( *ptr );
    }

    std::vector<PlcWaterLevelSensorStatus> waterLevelStatusList;
    for( auto& [id, ptr] : waterLevelSensorStatusMap_) {
        waterLevelStatusList.push_back( *ptr );
    }

    return BoxDeviceStatus(solenoidStatusList, cameraStatusList, sensorStatusList,
                           infraredSensorStatusList,smokeDetectorStatusList,waterLevelStatusList,doorLockStatusList);
}

bool DeviceStatusCache::isBoxDeviceStatusEmpty() {
    return solenoidStatusMap_.empty() && sensorStatusMap_.empty() && cameraStatusMap_.empty();
}


bool DeviceStatusCache::isSolenoidOpen( const PlcDeviceInfo& info) {
    auto it = solenoidStatusMap_.find(info.getDeviceId());

    if(it == solenoidStatusMap_.end())
        throw std::runtime_error("Solenoid device not found in cache");

    SolenoidStatus& status = *(it->second);
    return status.isOpen();
}

bool DeviceStatusCache::isSolenoidClose( const PlcDeviceInfo& info) {
    auto it = solenoidStatusMap_.find(info.getDeviceId());

    if(it == solenoidStatusMap_.end())
        throw std::runtime_error("Solenoid device not found in cache");

    SolenoidStatus& status = *(it->second);
    return !status.isOpen();
}

bool DeviceStatusCache::isDoorLockLock(const GPIODeviceSimpleInfo& info) {
    auto it = doorLockStatusMap_.find(info.getDeviceId());

    if(it == doorLockStatusMap_.end())
        throw std::runtime_error("Solenoid device not found in cache");

    DoorLockStatus& status = *(it->second);
    return status.isLock();
}

void DeviceStatusCache::updateSolenoidStatus( const SolenoidStatus& status ) {
    const std::string& deviceId = status.getDeviceId();

    auto it = solenoidStatusMap_.find(deviceId);
    if(it == solenoidStatusMap_.end()) 
        solenoidStatusMap_[deviceId] = std::make_unique<SolenoidStatus>(status);
    else *(it->second) = status;
}

void DeviceStatusCache::updateTempHumidSensorStatus( const TempHumidSensorStatus& status) {

    const std::string& deviceId = status.getDeviceId();
    auto it = sensorStatusMap_.find(deviceId);
    if(it == sensorStatusMap_.end())
        sensorStatusMap_[deviceId] = std::make_unique<TempHumidSensorStatus> (status);
    else *(it->second) = status;
}

void DeviceStatusCache::updateCameraStatus( const CameraStatus& status) {

    const std::string& deviceId = status.getDeviceId();

    auto it = cameraStatusMap_.find(deviceId);
    if(it == cameraStatusMap_.end())
        cameraStatusMap_[deviceId] = std::make_unique<CameraStatus>(status);
    else *(it->second) = status;
}

void DeviceStatusCache::updateInfraredSensorStatus(const InfraredSensorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = infraredSensorStatusMap_.find(deviceId);
    if(it == infraredSensorStatusMap_.end())
        infraredSensorStatusMap_[deviceId] = std::make_unique<InfraredSensorStatus>(status);
    else *(it->second) = status;
 }
void DeviceStatusCache::updatePlcWaterLevelSensorStatus(const PlcWaterLevelSensorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = waterLevelSensorStatusMap_.find(deviceId);
    if(it == waterLevelSensorStatusMap_.end())
        waterLevelSensorStatusMap_[deviceId] = std::make_unique<PlcWaterLevelSensorStatus>(status);
    else *(it->second) = status;
}
void DeviceStatusCache::updatePlcSmokeDetectorStatus(const PlcSmokeDetectorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = smokeDetectorStatusMap_.find(deviceId);
    if(it == smokeDetectorStatusMap_.end())
        smokeDetectorStatusMap_[deviceId] = std::make_unique<PlcSmokeDetectorStatus>(status);
    else *(it->second) = status;
}
void DeviceStatusCache::updateDoorLockStatus(const DoorLockStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = doorLockStatusMap_.find(deviceId);
    if(it == doorLockStatusMap_.end())
        doorLockStatusMap_[deviceId] = std::make_unique<DoorLockStatus>(status);
    else *(it->second) = status;
}
