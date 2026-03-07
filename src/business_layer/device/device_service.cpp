#include "device_service.h"
#include<optional>
DeviceService::DeviceService(DeviceManageService& deviceManageService,
                             DeviceStatusCache& deviceStatusCache,
                             DeviceAcquisitionTask& deviceAcuqisitionTask,
                             RealTimeFrameCache& realTimeFrameCache) 
    :_deviceManageService(deviceManageService),
     _deviceStatusCache(deviceStatusCache),
     _deviceAcquisitionTask(deviceAcuqisitionTask),
     _realTimeFrameCache(realTimeFrameCache)
{
    startTimer();
}

DeviceService::~DeviceService() {
    stopTimer();
}

BoxDeviceStatus DeviceService::viewAllDeviceStatus() {
    if (_deviceStatusCache.isBoxDeviceStatusEmpty()){
        const BoxDeviceStatus& devicesStatus = _deviceManageService.getBoxDeviceStatus();
        _deviceStatusCache.updateBoxDeviceStatus(devicesStatus);
        return devicesStatus;
    }
    
    const BoxDeviceStatus& devicesStatus = _deviceStatusCache.getBoxDeviceStatus();
    return devicesStatus;
}

BoxDeviceRealTimeData DeviceService::getBoxDeviceRealTimeData() {
    if(_deviceStatusCache.isBoxRealTimeDataEmpty()) {
        const BoxDeviceRealTimeData& realTimeData = _deviceManageService.getBoxDeviceRealTimeData();
        _deviceStatusCache.updateBoxDeviceRealTimeData(realTimeData);
        return realTimeData;
    }
    const BoxDeviceRealTimeData& realTimeData = _deviceStatusCache.getBoxDeviceRealTimeData();
    return realTimeData;
}

DeviceOperationResult DeviceService::openSolenoidValue( const SolenoidValueInfo& info) {
    if(_deviceStatusCache.isSolenoidOpened(info))
        return new DeviceOperationResult(-1,"电磁阀已经打开!");
    _deviceManageService.openSolenidValue(info);
    return new DeviceOperationResult(0,"电磁阀打开成功!");
}

DeviceOperationResult DeviceService::closeSolenoidValue( const SolenoidValueInfo& info) {
    if(_deviceStatusCache.isSolenoidClosed(info))
        return new DeviceOperationResult(-1,"电磁阀已经关闭!");

    return _deviceManageService.closeSolenoidValue(info);
}

DeviceOperationResult DeviceService::controlCarRotation( const CarControl& car) {
    return _deviceManageService.controlCarRotation(car);
}

CameraRealTimeFrame DeviceService::getCameraRealTimeFrame( const CameraInfo& info) {
    return _realTimeFrameCache.getCameraRealTimeFrame(info);
}

CameraHistoryVideo DeviceService::viewCameraHistoryVideo( const CameraInfo& info) {
    return _deviceManageService.getCameraHistoryVideo(info);
}

RadarPointCloud DeviceService::getRadarPointCloudData( const RadarInfo& info) {
    return _deviceManageService.getRadarPointCloudData(info);
}

BoxConfigResult DeviceService::configBoxDeviceParams( const BoxDeviceParam& params) {
    return _deviceManageService.BoxDeviceParamConfig(params);
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
    std::vector<std::unique_ptr<DeviceData> > deviceData = _deviceManageService.deviceDataAcquisition(deviceType);
    //更新一种设备的状态和实时数据
    _deviceStatusCache.updateDeviceStatus(deviceData);
    _deviceStatusCache.updateDeviceRealTimeData(deviceData);
}

void DeviceService::timerLoop() {
    using namespace std::chrono;

    while(_running) {
        auto startTime = steady_clock::now();

        for(auto& task : _deviceAcquisitionTask.getTasks()) {
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