#include "business_layer/device/device_service.h"
#include<optional>
#include <iostream>
DeviceService::DeviceService(DeviceManageService& deviceManageService,
                             DeviceStatusCache& deviceStatusCache,
                             DeviceAcquisitionTask& deviceAcuqisitionTask,
                             RealTimeFrameCache& realTimeFrameCache) 
    : deviceManageService_(deviceManageService),
      deviceStatusCache_(deviceStatusCache),
      deviceAcquisitionTask_(deviceAcuqisitionTask),
      realTimeFrameCache_(realTimeFrameCache)
{
    startTimer();
}

DeviceService::~DeviceService() {
    stopTimer();
}

BoxDeviceStatus DeviceService::viewAllDeviceStatus() {
    if (deviceStatusCache_.isBoxDeviceStatusEmpty()){
        const BoxDeviceStatus& devicesStatus = deviceManageService_.getDeviceStatus();
        deviceStatusCache_.updateBoxDeviceStatus(devicesStatus);
        return devicesStatus;
    }
    
    const BoxDeviceStatus& devicesStatus = deviceStatusCache_.getBoxDeviceStatus();
    return devicesStatus;
}


int DeviceService::openSolenoidValue(const PlcDeviceInfo& info) {
    if(deviceStatusCache_.isSolenoidOpen(info))
        return 1;
    return deviceManageService_.openSolenoidValue(info);
    
}

int DeviceService::closeSolenoidValue(const PlcDeviceInfo& info) {
    if(deviceStatusCache_.isSolenoidClose(info))
        return 1;

    return deviceManageService_.closeSolenoidValue(info);
}

int DeviceService::lockDoorLock(const GPIODeviceSimpleInfo& info) {
    if(deviceStatusCache_.isDoorLockLock(info)){
        std::cout << "执行从缓存中的操作" << std::endl;
        return 1;
    }
        
    return deviceManageService_.lockDoorLock(info);
}

int DeviceService::unlockDoorLock(const GPIODeviceSimpleInfo& info) {
    if(!deviceStatusCache_.isDoorLockLock(info))
        return 1;
    return deviceManageService_.unlockDoorLock(info);
}

// DeviceOperationResult DeviceService::controlCarRotation( const CarControl& car) {
//     return deviceManageService_.controlCarRotation(car);
// }

// RadarPointCloud DeviceService::getRadarPointCloudData( const RadarInfo& info) {
//     return deviceManageService_.getRadarPointCloudData(info);
// }

// BoxConfigResult DeviceService::configBoxDeviceParams( const BoxDeviceParam& params) {
//     return deviceManageService_.boxDeviceParamsConfig(params);
// }

SolenoidStatus DeviceService::getSolenoidValueStatus(const PlcDeviceInfo& info) {
    if(!deviceStatusCache_.findSolenoidStatus(info.getDeviceId()))
        return deviceManageService_.querySolenoidValueStatus(info);
    else return deviceStatusCache_.getSolenoidValueStatus(info.getDeviceId());
}
TempHumidSensorStatus DeviceService::getTempHumidSensorStatus(const SerialDirectDeviceInfo& info) {
    if(!deviceStatusCache_.findTempHumidSensorStatus(info.getDeviceId()))
        return deviceManageService_.queryTempHumidSensorStatus(info.getDeviceId());
    return deviceStatusCache_.getTempHumidSensorStatus(info.getDeviceId());
}
InfraredSensorStatus DeviceService::getInfraredSensorStatus(const GPIODeviceSimpleInfo& info) {
    if(!deviceStatusCache_.findInfraredSensorStatus(info.getDeviceId())) {
        return deviceManageService_.queryInfraredSensorStatus(info.getDeviceId());
    }
       
    return deviceStatusCache_.getInfraredSensorStatus(info.getDeviceId());
}
SmokeDetectorStatus DeviceService::getSmokeDetectorStatus(const GPIODeviceSimpleInfo& info) {
    if(!deviceStatusCache_.findSmokeDetectorStatus(info.getDeviceId()))
        return deviceManageService_.querySmokeDetectorStatus(info.getDeviceId());
    return deviceStatusCache_.getSmokeDetectorStatus(info.getDeviceId());
}
WaterLevelSensorStatus DeviceService::getWaterLevelSensorStatus(const GPIODeviceSimpleInfo& info) {
    if(!deviceStatusCache_.findWaterLevelSensorStatus(info.getDeviceId()))  
        return deviceManageService_.queryWaterLevelSensorStatus(info.getDeviceId());
    return deviceStatusCache_.getWaterLevelSensorStatus(info.getDeviceId());
}

void DeviceService::updateSolenoidStatus(const SolenoidStatus& status) {
    deviceStatusCache_.updateSolenoidStatus(status);
}

void DeviceService::updateTempHumidSensorStatus(const TempHumidSensorStatus& status) {
    deviceStatusCache_.updateTempHumidSensorStatus(status);
}

void DeviceService::updateInfraredSensorStatus(const InfraredSensorStatus& status) {
    deviceStatusCache_.updateInfraredSensorStatus(status);
}

void DeviceService::updateSmokeDetectorStatus(const SmokeDetectorStatus& status) {
    deviceStatusCache_.updateSmokeDetectorStatus(status);
}

void DeviceService::updateWaterLevelSensorStatus(const WaterLevelSensorStatus& status) {
    deviceStatusCache_.updateWaterLevelSensorStatus(status);
}


void DeviceService::startTimer() {
    _running = true;

    _timerThread = std::thread(&DeviceService::timerLoop,this);
}

void DeviceService::stopTimer() {
    _running = false;

    if(_timerThread.joinable()) _timerThread.join();
}

void DeviceService::devicesDataCollection(int deviceType) {
    
    // 设备数据采集 DeviceData 父类
    std::vector<DeviceData> deviceData = deviceManageService_.deviceDataAcquisition(deviceType);
    //更新一种设备的状态和实时数据
    deviceStatusCache_.updateDeviceStatus(deviceData);
}

void DeviceService::timerLoop() {
    using namespace std::chrono;

    while(_running) {
        std::cout <<"执行中" <<std::endl;
        auto startTime = steady_clock::now();

        for(const auto& task : deviceAcquisitionTask_.getTasks()) {
            if(task->isAcquisitionData()) 
                devicesDataCollection(task->getType());
        }
        std::this_thread::sleep_for(seconds(1));

    }
}
// void DeviceService::timerLoop() {
//     using namespace std::chrono;
//     auto nextTick = steady_clock::now();

//     while(_running) {
//         nextTick += seconds(1);

//         executeTasks();

//         std::unique_lock<std::mutex> lock(_mutex);
//         _cv.wait_until(lock, nextTick, [this]{
//             return !_running;
//         });
//     }
// }