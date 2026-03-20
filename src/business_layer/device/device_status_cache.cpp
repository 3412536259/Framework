#include "business_layer/device/device_status_cache.h"

#include <functional>
DeviceStatusCache::DeviceStatusCache() {
    solenoidStatusMap_.clear(); 
    solenoidStatusMap_.reserve(16);
    sensorStatusMap_.clear();   
    sensorStatusMap_.reserve(8);
    cameraStatusMap_.clear();   
    cameraStatusMap_.reserve(4);
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
        case 2:
            for(auto& camera : deviceDataList)
                updateCameraStatus(camera.getCameraStatus());
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
                updatePlcSmokeDetectorStatus(smokeDetector.getPlcSmokeDetectorStatus());
            break;
        case 6:
            for(auto& waterLevelSensor : deviceDataList)
                updatePlcWaterLevelSensorStatus(waterLevelSensor.getPlcWaterLevelSensorStatus());
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

    std::vector<CameraStatus> cameraStatusList;
    for( auto& [id, camera] : cameraStatusMap_) {
        cameraStatusList.push_back( camera );
    }

    std::vector<DoorLockStatus> doorLockStatusList;
    for( auto& [id, doorLock] : doorLockStatusMap_) {
        doorLockStatusList.push_back( doorLock );
    }

    std::vector<InfraredSensorStatus> infraredSensorStatusList;
    for( auto& [id, sensor] : infraredSensorStatusMap_) {
        infraredSensorStatusList.push_back( sensor );
    }

    std::vector<PlcSmokeDetectorStatus> smokeDetectorStatusList;
    for( auto& [id, detector] : smokeDetectorStatusMap_) {
        smokeDetectorStatusList.push_back( detector );
    }

    std::vector<PlcWaterLevelSensorStatus> waterLevelStatusList;
    for( auto& [id, sensor] : waterLevelSensorStatusMap_) {
        waterLevelStatusList.push_back( sensor );
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

    if(it == doorLockStatusMap_.end())
        throw std::runtime_error("Solenoid device not found in cache");

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

void DeviceStatusCache::updateCameraStatus( const CameraStatus& status) {

    const std::string& deviceId = status.getDeviceId();

    auto it = cameraStatusMap_.find(deviceId);
    if(it == cameraStatusMap_.end())
        cameraStatusMap_[deviceId] = status;
    else it->second = status;
}

void DeviceStatusCache::updateInfraredSensorStatus(const InfraredSensorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = infraredSensorStatusMap_.find(deviceId);
    if(it == infraredSensorStatusMap_.end())
        infraredSensorStatusMap_[deviceId] = status;
    else it->second = status;
 }
void DeviceStatusCache::updatePlcWaterLevelSensorStatus(const PlcWaterLevelSensorStatus& status) {
    const std::string& deviceId = status.getDeviceId();

    auto it = waterLevelSensorStatusMap_.find(deviceId);
    if(it == waterLevelSensorStatusMap_.end())
        waterLevelSensorStatusMap_[deviceId] = status;
    else it->second = status;
}
void DeviceStatusCache::updatePlcSmokeDetectorStatus(const PlcSmokeDetectorStatus& status) {
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
