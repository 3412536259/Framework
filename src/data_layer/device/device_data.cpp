#include "device_data.h"

DeviceData::DeviceData(int type,const SolenoidStatus solenoidStatus,const SolenoidRealTimeData solenoidRealTimeData) 
    : type(type), solenoidStatus(solenoidStatus), solenoidRealTimeData(solenoidRealTimeData) {

}

DeviceData::DeviceData(int type,const Sensorstatus sensorStatus,const SensorRealTimeData sensorRealTimeData) 
    : type(type), sensorStatus(sensorStatus), sensorRealTimeData(sensorRealTimeData) {

}

DeviceData::DeviceData(int type,const CameraStatus cameraStatus) 
    : type(type), cameraStatus(cameraStatus) {

}

int DeviceData::getType() const {
    return type;
}

SolenoidStatus DeviceData::getSolenoidStatus() const {
    return solenoidStatus;
}

SolenoidRealTimeData DeviceData::getSolenoidRealTimeData() const {
    return solenoidRealTimeData;
}   

SensorStatus DeviceData::getSensorStatus() const {
    return sensorStatus;
}   

SensorRealTimeData DeviceData::getSensorRealTimeData() const {
    return sensorRealTimeData;
}

CameraStatus DeviceData::getCameraStatus() const {
    return cameraStatus;
}