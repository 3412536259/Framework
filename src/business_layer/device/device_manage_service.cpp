#include "device_manage_service.h"
#include "solenoid_value.h"
#include <vector>

DeviceManageService::DeviceManageService(BoxInstance boxInstance,
                                         SolenoidInstanceSet solenoidInstances,
                                         CameraInstanceSet cameraInstances,
                                         SensorInstanceSet sensorInstances) 
    :   boxInstance_(boxInstance),solenoidInstances_(solenoidInstances),
        cameraInstances_(cameraInstances),sensorInstances_(sensorInstances) 
{

}

DeviceManageService::~DeviceManageService() {

}

BoxDeviceStatus DeviceManageService::getDeviceStatus() {
    const std::vector<SolenoidStatus> solenoidValues = solenoidInstanceSet_.getSolenoidStatusList();
    const std::vector<CameraStatus> cameras = cameraInstanceSet_.getCameraStatusList();
    const std::vector<SensorStatus> sensors = sensorInstanceSet_.getSensorStatusList();
    // const std::vector<RadarStatus> radars = _radarInstanceSet.getRadars();
    // const std::vector<CarStatus> cars = _carInstanceSet.getCars();

    return new BoxDeviceStatus(solenoidValues, cameras, sensors);
}

BoxDeviceRealTimeData DeviceManageService::getDeviceRealTimeData() {
    const std::vector<SolenoidRealTimeData> solenoids = solenoidInstanceSet_.getSolenoidRealTimeDataList();
    // const std::vector<CameraRealTimeData> cameras = _cameraInstanceSet.getCameraRealTimeDataList();
    const std::vector<SensorRealTimeData> sensors = sensorInstanceSet_.getSensorRealTimeDataList();
    // const std::vector<RadarRealTimeData> radars = _radarInstanceSet.getRadarRealTimeData();
    // const std::vector<CarRealTimeData> cars = _carInstanceSet.getCarRealTimeData();

    return new BoxDeviceRealTimeData(solenoids,sensors);
}

DeviceOperationResult DeviceManageService::openSolenoidValue( const SolenoidValueInfo& info) {
    int result = solenoidInstanceSet_.openSolenoidValue(info);
    if (result == 0 ) return new DeviceOperationResult(0,"打开成功"); 
    return new DeviceOperationResult(result,"打开失败");
}

DeviceOperationResult DeviceManageService::closeSolenoidValue( const SolenoidValueInfo& info) {
    int result = solenoidInstanceSet_.closeSolenoidValue(info);
    if( result == 0 ) return new DeviceOperationResult(0,"关闭成功");
    return new DeviceOperationResult(result,"关闭失败");
}

// DeviceOperationResult DeviceManageService::controlCarRotation( const CarControl& car) {
//     int result = _carInstanceSet.controlCarRotation(car);
//     return new DeviceOperationResult(result, "控制成功" );
// }

CameraHistoryVideo DeviceManageService::getCameraHistoryVideo( const CameraInfo& info) {
    return cameraInstanceSet_.getCameraHistoryVideo(info.getDeviceId());
}

// RadarPointCloud DeviceManageService::getRadarPointCloudData( const RadarInfo& info) {
//     return radarInstanceSet_.getRadarPointCloudData(info.getDeviceId());
// }

BoxConfigResult DeviceManageService::boxDeviceParamsConfig( const BoxDeviceParam& params) {
    return boxInstance_.configBoxDeviceParams(params);
}

std::vector<std::unique_ptr<DeviceData> > DeviceManageService::deviceDataAcquisition(int deviceType) {
    if(deviceType == 0) {
        return solenoidInstanceSet_.acquisitionSolenoidData();
    }else if(deviceType == 1) {
        return sensorInstanceSet_.acquisitionSensorData();
    }else if(deviceType == 2) {
        return cameraInstanceSet_.acquisitionCameraData();
    }
}