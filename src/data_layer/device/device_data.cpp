#include "data_layer/device/device_data.h"

DeviceData::DeviceData(int type,const SolenoidStatus solenoidStatus) 
    : type(type), solenoidStatus_(solenoidStatus){

}

DeviceData::DeviceData(int type,const TempHumidSensorStatus sensorStatus) 
    : type(type), sensorStatus_(sensorStatus) {

}

DeviceData::DeviceData(int type,const DoorLockStatus doorLockStatus) 
    : type(type), doorLockStatus_(doorLockStatus) {

}
DeviceData::DeviceData(int type,const InfraredSensorStatus infraredSensorStatus) 
    : type(type), infraredSensorStatus_(infraredSensorStatus) {

}
DeviceData::DeviceData(int type,const SmokeDetectorStatus smokeDetectorStatus) 
    : type(type), smokeDetectorStatus_(smokeDetectorStatus) {

}
DeviceData::DeviceData(int type,const WaterLevelSensorStatus waterLevelSensorStatus) 
    :type(type), waterLevelSensorStatus_(waterLevelSensorStatus) {

}

int DeviceData::getType() const {
    return type;
}

SolenoidStatus DeviceData::getSolenoidStatus() const {
    return solenoidStatus_;
}

TempHumidSensorStatus DeviceData::getSensorStatus() const {
    return sensorStatus_;
}   

DoorLockStatus DeviceData::getDoorLockStatus() const {
    return doorLockStatus_;
}
InfraredSensorStatus DeviceData::getInfraredSensorStatus() const {
    return infraredSensorStatus_;
}
SmokeDetectorStatus DeviceData::getSmokeDetectorStatus() const {
    return smokeDetectorStatus_;
}
WaterLevelSensorStatus DeviceData::getWaterLevelSensorStatus() const {
    return waterLevelSensorStatus_;
}