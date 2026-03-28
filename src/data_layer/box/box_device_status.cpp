#include "data_layer/box/box_device_status.h"

BoxDeviceStatus::BoxDeviceStatus(const std::vector<SolenoidStatus> solenoidStatuses,
                                 const std::vector<TempHumidSensorStatus> sensorStatuses,
                                 const std::vector<InfraredSensorStatus> infraredSensorStatuses,
                                 const std::vector<SmokeDetectorStatus> smokeDetectorStatuses,
                                 const std::vector<WaterLevelSensorStatus> waterSensorStatuses,
                                 const std::vector<DoorLockStatus> doorLockStatuses)
    : solenoidStatuses_(solenoidStatuses),
      sensorStatuses_(sensorStatuses),
      infraredSensorStatuses_(infraredSensorStatuses),
      smokeDetectorStatuses_(smokeDetectorStatuses),
      waterSensorStatuses_(waterSensorStatuses),
      doorLockStatuses_(doorLockStatuses) {

}

std::vector<SolenoidStatus> BoxDeviceStatus::getSolenoidStatusList() const {
  return solenoidStatuses_;
}

std::vector<TempHumidSensorStatus> BoxDeviceStatus::getSensorStatusList() const {
  return sensorStatuses_;
}

std::vector<InfraredSensorStatus> BoxDeviceStatus::getInfraredSensorStatusList() const {
  return infraredSensorStatuses_;
}
std::vector<SmokeDetectorStatus> BoxDeviceStatus::getSmokeDetectorStatusList() const {
  return smokeDetectorStatuses_;
}
std::vector<WaterLevelSensorStatus> BoxDeviceStatus::getWaterLevelSensorStatusList() const {
  return waterSensorStatuses_;
}

std::vector<DoorLockStatus> BoxDeviceStatus::getDoorLockStatusList() const {
  return doorLockStatuses_;
}

