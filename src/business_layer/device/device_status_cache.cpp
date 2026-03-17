#include "device_status_cache.h"

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

    const std::vector<SensorStatus> sensorStatusList = devices.getSensorStatusList();
    for( auto& sensorStatus : sensorStatusList) {
        updateSensorStatus(sensorStatus);
    }
    const std::vector<CameraStatus>& cameraStatusList = devices.getCameraStatusList();
    for( auto& cameraStatus : cameraStatusList) {
        updateCameraStatus(cameraStatus);
    }
}

void DeviceStatusCache::updateDeviceStatus( const std::vector<std::unique_ptr<DeviceData> >& deviceDataList ) {
    const DeviceData& deviceData = *deviceDataList.front();
    if(deviceData.getType() == 0) {
        for(auto& solenoidPtr : deviceDataList)
            updateSolenoidStatus( solenoidPtr.getStatus());  
    }
    else if(deviceData.getType() == 1) {
        for(auto& sensorPtr : deviceDataList)
            updateSensorStatus(sensorPtr.getStatus());
    }
    else if(deviceData.getType() == 2) {
        for(auto& cameraPtr : deviceDataList)
            updateCameraStatus(cameraPtr.getStatus());
    }
}

void DeviceStatusCache::updateBoxDeviceRealTimeData( const BoxDeviceRealTimeData& boxDeviceData) {
    const std::vector<SolenoidRealTimeData>& solenoidRealTimeDataList = boxDeviceData.getSolenoidRealTimeDataList();
    for( auto& solenoidRealTimeData : solenoidRealTimeDataList) {
        updateSolenoidRealTimeData(solenoidRealTimeData);
    } 

    const std::vector<SensorRealTimeData>& sensorRealTimeDataList = boxDeviceData.getSensorRealTimeDataList();
    for( auto& sensorRealTimeData : sensorRealTimeDataList) {
        updateSensorRealTimeData(sensorRealTimeData);
    }

    // const std::vector<CameraRealTimeData>& cameraRealTimeDataList = boxDeviceData.getCameraRealTimeDataList();
    // for( auto& cameraRealTimeData : cameraRealTimeDataList) {
    //     updateCameraRealTimeData(cameraRealTimeData);
    // }
}

void DeviceStatusCache::updateDeviceRealTimeData( const std::vector<std::unique_ptr<DeviceData> >& deviceDataList) {
    const DeviceData& deviceData = *deviceDataList.front();
    if(deviceData.getType() == 0) {
        for(auto& solenoidPtr : deviceDataList)
            updateSolenoidRealTimeData( solenoidPtr.getRealTimeData());
    }
    else if(deviceData.getType() == 1) {
        for(auto& sensorPtr : deviceDataList)
            updateSensorRealTimeData(sensorPtr.getRealTimeData());
    }
   
}

BoxDeviceStatus DeviceStatusCache::getBoxDeviceStatus() {
    std::vector<std::reference_wrapper<SolenoidStatus> > solenoidStatusList;
    for( auto& [id, ptr] : _solenoidStatusMap) {
        solenoidStatusList.push_back( *ptr );
    }

    std::vector<std::reference_wrapper<SensorStatus> > sensorStatusList;
    for( auto& [id, ptr] : _sensorStatusMap) {
        sensorStatusList.push_back( *ptr );
    }

    std::vector<std::reference_wrapper<CameraStatus> > cameraStatusList;
    for( auto& [id, ptr] : _cameraStatusMap) {
        cameraStatusList.push_back( *ptr );
    }
    return new BoxDeviceStatus(solenoidStatusList, sensorStatusList, cameraStatusList);
}

BoxDeviceRealTimeData DeviceStatusCache::getBoxDeviceRealTimeData() {
    std::vector<std::reference_wrapper<SolenoidRealTimeData> > solenoidRealTimeDataList;
    for( auto& [id, ptr] : _solenoidRealTimeDataMap) {
        solenoidRealTimeDataList.push_back( *ptr );
    }

    std::vector<std::reference_wrapper<SensorRealTimeData> > sensorRealTimeDataList;
    for( auto& [id, ptr] : _sensorRealTimeDataMap) {
        sensorRealTimeDataList.push_back( *ptr );
    }

    return new BoxDeviceRealTimeData(solenoidRealTimeDataList, sensorRealTimeDataList);
}

bool DeviceStatusCache::isBoxDeviceStatusEmpty() {
    return _solenoidStatusMap.empty() && _sensorStatusMap.empty() && _cameraStatusMap.empty();
}

bool DeviceStatusCache::isBoxRealTimeDataEmpty() {
    return _solenoidRealTimeDataMap.empty() && _sensorRealTimeDataMap.empty() && _cameraRealTimeDataMap.empty();
}

bool DeviceStatusCache::isSolenoidOpen( const SolenoidValueInfo& info) {
    auto it = _solenoidRealTimeDataMap.find(info.getDeviceId());

    if(it == _solenoidRealTimeDataMap.end())
        throw std::runtime_error("Solenoid device not found in cache");

    SolenoidRealTimeData& realTimeData = *(it->second);
    return realTimeData.isOpen();
}

bool DeviceStatusCache::isSolenoidClose( const SolenoidValueInfo& info) {
    auto it = _solenoidRealTimeDataMap.find(info.getDeviceId());

    if(it == _solenoidRealTimeDataMap.end())
        throw std::runtime_error("Solenoid device not found in cache");

    SolenoidRealTimeData& realTimeData = *(it->second);
    return !realTimeData.isOpen();
}

void DeviceStatusCache::updateSolenoidStatus( const SolenoidStatus& status ) {
    const std::string& deviceId = status.getDeviceId();

    auto it = _solenoidStatusMap.find(deviceId);
    if(it == _solenoidStatusMap.end()) 
        _solenoidStatusMap[deviceId] = std::make_unique<SolenoidStatus>(status);
    else *(it->second) = status;
}

void DeviceStatusCache::updateSensorStatus( const SensorStatus& status) {

    const std::string& deviceId = status.getDeviceId();
    auto it = _sensorStatusMap.find(deviceId);
    if(it == _sensorStatusMap.end())
        _sensorStatusMap[deviceId] = std::make_unique<SensorStatus> (status);
    else *(it->second) = status;
}

void DeviceStatusCache::updateCameraStatus( const CameraStatus& status) {

    const std::string& deviceId = status.getDeviceId();

    auto it = _cameraStatusMap.find(deviceId);
    if(it == _cameraStatusMap.end())
        _cameraStatusMap[deviceId] = std::make_unique<CameraStatus>(status);
    else *(it->second) = status;
}

void DeviceStatusCache::updateSolenoidRealTimeData( const SolenoidRealTimeData& data) {

    const std::string& deviceId = data.getDeviceId();

    auto it = _solenoidRealTimeDataMap.find(deviceId);
    if(it == _solenoidRealTimeDataMap.end())
        _solenoidRealTimeDataMap[deviceId] = std::make_unique<SolenoidRealTimeData>(data);
    else *(it->second) = data;
}

void DeviceStatusCache::updateSensorRealTimeData( const SensorRealTimeData& data) {
    const std::string& deviceId = data.getDeviceId();

    auto it = _sensorRealTimeDataMap.find(deviceId);
    if(it == _sensorRealTimeDataMap.end())
        _sensorRealTimeDataMap[deviceId] = std::make_unique<SensorRealTimeData>(data);
    else *(it->second) = data;
}