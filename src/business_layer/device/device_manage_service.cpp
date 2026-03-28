#include "business_layer/device/device_manage_service.h"
// #include "solenoid_value.h"
#include <vector>

DeviceManageService::DeviceManageService(
                                         PlcInstanceSet&& plcInstances,
                                         GPIODeviceInstanceSet&& gpioInstanceSet,
                                         SerialDirectDeviceInstanceSet&& serialInstances) 
    :   plcInstances_(std::move(plcInstances)),
        gpioInstanceSet_(std::move(gpioInstanceSet)),serialInstances_(std::move(serialInstances)) 
{

}

DeviceManageService::~DeviceManageService() {

}

BoxDeviceStatus DeviceManageService::getDeviceStatus() {
    const std::vector<SolenoidStatus> solenoidValues = plcInstances_.getPlcSolenoidStatusList();
    const std::vector<InfraredSensorStatus> infraredSensorStatuses = gpioInstanceSet_.getInfraredSensorStatusList();
    const std::vector<SmokeDetectorStatus> smokeDetectorStatuses = gpioInstanceSet_.getSmokeDetectorStatusList();
    const std::vector<WaterLevelSensorStatus> waterSensores = gpioInstanceSet_.getWaterLevelSensorStatusList();
    const std::vector<TempHumidSensorStatus> tempHumidSensors = serialInstances_.getSensorStatusList();
    const std::vector<DoorLockStatus> doorLocks = gpioInstanceSet_.getDoorLockStatusList();
    // const std::vector<RadarStatus> radars = _radarInstanceSet.getRadars();
    // const std::vector<CarStatus> cars = _carInstanceSet.getCars();

    return BoxDeviceStatus(solenoidValues, tempHumidSensors,infraredSensorStatuses,smokeDetectorStatuses,waterSensores,doorLocks);
}

SolenoidStatus DeviceManageService::querySolenoidValueStatus(const PlcDeviceInfo& info) {
    return plcInstances_.getPlcSolenoidStatus(info);
}
TempHumidSensorStatus DeviceManageService::queryTempHumidSensorStatus(const std::string& deviceId) {
    return serialInstances_.getSensorStatus(deviceId);
}
InfraredSensorStatus DeviceManageService::queryInfraredSensorStatus(const std::string& deviceId) {
    return gpioInstanceSet_.getInfraredSensorStatus(deviceId);
}
SmokeDetectorStatus DeviceManageService::querySmokeDetectorStatus(const std::string& deviceId) {
    return gpioInstanceSet_.getSmokeDetectorStatus(deviceId);
}
WaterLevelSensorStatus DeviceManageService::queryWaterLevelSensorStatus(const std::string& deviceId) {
    return gpioInstanceSet_.getWaterLevelSensorStatus(deviceId);
}


int DeviceManageService::openSolenoidValue(const PlcDeviceInfo& info) {
    if(plcInstances_.openPlcSolenoid(info)) return 0; 
    return -1;
}

int DeviceManageService::closeSolenoidValue(const PlcDeviceInfo& info) {
    if(plcInstances_.closePlcSolenoid(info)) return 0;
    return -1;
}

int DeviceManageService::lockDoorLock(const GPIODeviceSimpleInfo& info) {
    if(gpioInstanceSet_.lockDoorLock(info)) return 0;
    return -1;
}
int DeviceManageService::unlockDoorLock(const GPIODeviceSimpleInfo& info) {
    if(gpioInstanceSet_.unlockDoorLock(info)) return 0;
    return -1;
}

// DeviceOperationResult DeviceManageService::controlCarRotation( const CarControl& car) {
//     int result = _carInstanceSet.controlCarRotation(car);
//     return new DeviceOperationResult(result, "控制成功" );
// }

// RadarPointCloud DeviceManageService::getRadarPointCloudData( const RadarInfo& info) {
//     return radarInstanceSet_.getRadarPointCloudData(info.getDeviceId());
// }

// BoxConfigResult DeviceManageService::boxDeviceParamsConfig( const BoxDeviceParam& params) {
//     return boxInstance_.configBoxDeviceParams(params);
// }

std::vector<DeviceData> DeviceManageService::deviceDataAcquisition(int deviceType) {
    switch(deviceType) {
        case 0: return plcInstances_.acquisitionPlcSolenoidData();
        case 1: return serialInstances_.acquisitionTempHumidSensorData();
        case 3: return gpioInstanceSet_.acquisitionDoorLockData();
        case 4: return gpioInstanceSet_.acquisitionInfraredSensorData();
        case 5: return gpioInstanceSet_.acquisitionSmokeDetectorData();
        case 6: return gpioInstanceSet_.acquisitionWaterLevelSensorData();
        default: return {};
    }
    
}