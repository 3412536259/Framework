#include "business_layer/device/device_service.h"
#include<optional>
DeviceService::DeviceService(DeviceManageService& deviceManageService,
                             DeviceStatusCache& deviceStatusCache,
                             DeviceAcquisitionTask& deviceAcuqisitionTask,
                             RealTimeFrameCache& realTimeFrameCache) 
    :deviceManageService_(deviceManageService),
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
    if (_deviceStatusCache.isBoxDeviceStatusEmpty()){
        const BoxDeviceStatus& devicesStatus = deviceManageService_.getDeviceStatus();
        deviceStatusCache_.updateBoxDeviceStatus(devicesStatus);
        return devicesStatus;
    }
    
    const BoxDeviceStatus& devicesStatus = deviceStatusCache_.getBoxDeviceStatus();
    return devicesStatus;
}

BoxDeviceRealTimeData DeviceService::getBoxDeviceRealTimeData() {
    if(_deviceStatusCache.isBoxRealTimeDataEmpty()) {
        const BoxDeviceRealTimeData& realTimeData = deviceManageService_.getBoxDeviceRealTimeData();
        deviceStatusCache_.updateBoxDeviceRealTimeData(realTimeData);
        return realTimeData;
    }
    const BoxDeviceRealTimeData& realTimeData = deviceStatusCache_.getBoxDeviceRealTimeData();
    return realTimeData;
}

DeviceOperationResult DeviceService::openSolenoidValue( const SolenoidValueInfo& info) {
    if(deviceStatusCache_.isSolenoidOpen(info))
        return new DeviceOperationResult(-1,"电磁阀已经打开!");
    deviceManageService_.openSolenoidValue(info);
    return new DeviceOperationResult(0,"电磁阀打开成功!");
}

DeviceOperationResult DeviceService::closeSolenoidValue( const SolenoidValueInfo& info) {
    if(deviceStatusCache_.isSolenoidClose(info))
        return new DeviceOperationResult(-1,"电磁阀已经关闭!");

    return deviceManageService_.closeSolenoidValue(info);
}

DeviceOperationResult DeviceService::controlCarRotation( const CarControl& car) {
    return deviceManageService_.controlCarRotation(car);
}

CameraRealTimeFrame DeviceService::getCameraRealTimeFrame( const CameraInfo& info) {
    return realTimeFrameCache_.getCameraRealTimeFrame(info);
}

CameraHistoryVideo DeviceService::viewCameraHistoryVideo( const CameraInfo& info) {
    return deviceManageService_.getCameraHistoryVideo(info);
}

RadarPointCloud DeviceService::getRadarPointCloudData( const RadarInfo& info) {
    return deviceManageService_.getRadarPointCloudData(info);
}

BoxConfigResult DeviceService::configBoxDeviceParams( const BoxDeviceParam& params) {
    return deviceManageService_.boxDeviceParamsConfig(params);
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
    std::vector<std::unique_ptr<DeviceData> > deviceData = deviceManageService_.deviceDataAcquisition(deviceType);
    //更新一种设备的状态和实时数据
    deviceStatusCache_.updateDeviceStatus(deviceData);
    deviceStatusCache_.updateDeviceRealTimeData(deviceData);
}

void DeviceService::timerLoop() {
    using namespace std::chrono;

    while(_running) {
        auto startTime = steady_clock::now();

        for(auto& task : deviceAcquisitionTask_.getTasks()) {
            if(task->isAcquisitionData()) 
                devicesDataCollection(task->getType());
        }
        std::this_thread::sleep_for(seconds(1));

        // auto endTime = steady_clock::now();
        // auto elapsed = duration_cast<milliseconds>(endTime - startTime);

        // auto sleepTime = milliseconds(1000) - elapsed;

        // if(sleepTime > milliseconds(0)) std::this_thread::sleep_for(sleepTime);
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