#include "device_manage_service.h"
#include "solenoid_value.h"
#include <vector>
BoxDeviceStatus DeviceManageService::getDeviceStatus() {
    const std::vector<SolenoidValue> solenoidValues = _solenoidInstanceSet.getSolenoidValues();
    const std::vector<Camera> cameras = _cameraInstanceSet.getCameras();
    const std::vector<Sensor> sensors = _sensorInstanceSet.getSensors();
    const std::vector<Radar> radars = _radarInstanceSet.getRadars();
    const std::vector<Car> cars = _carInstanceSet.getCars();

    return new BoxDeviceStatus(solenoidValues, cameras, sensors, radars, cars);
}

BoxDeviceRealTimeData DeviceManageService::getDeviceRealTimeData() {
    const std::vector<SolenoidRealTimeData> solenoids = _solenoidInstanceSet.getSolenoidRealTimeData();
    const std::vector<CameraRealTimeData> cameras = _cameraInstanceSet.getCameraRealTimeData();
    const std::vector<SensorRealTimeData> sensors = _sensorInstanceSet.getSensorRealTimeData();
    const std::vector<RadarRealTimeData> radars = _radarInstanceSet.getRadarRealTimeData();
    const std::vector<CarRealTimeData> cars = _carInstanceSet.getCarRealTimeData();

    return new BoxDeviceRealTimeData(solenoids, cameras, sensors, radars, cars);
}

DeviceOperationResult DeviceManageService::openSolenoidValue( const SolenoidValueInfo& info) {
    int result = _solenoidInstanceSet.openSolenoidValue(info);
    if (result == 0 ) return new DeviceOperationResult(0,"打开成功"); 
    return new DeviceOperationResult(result,"打开失败");
}

DeviceOperationResult DeviceManageService::closeSolenoidValue( const SolenoidValueInfo& info) {

}

DeviceOperationResult DeviceManageService::controlCarRotation( const CarControl& car) {

}

CameraHistoryVideo DeviceManageService::getCameraHistoryVideo( const CameraInfo& info) {

}

RadarPointCloudData DeviceManageService::getRadarPointCloudData( const RadarInfo& info) {

}

BoxConfigResult DeviceManageService::BoxDeviceParamsConfig( const BoxDeviceParams& params) {

}