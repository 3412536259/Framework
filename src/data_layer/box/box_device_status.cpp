#include "box_device_status.h"

BoxDeviceStatus::BoxDeviceStatus(const std::vector<SolenoidStatus>& solenoidStatuses,
                                 const std::vector<CameraStatus>& cameraStatuses,
                                 const std::vector<SensorStatus>& sensorStatuses)
    : solenoidStatuses_(solenoidStatuses),
      cameraStatuses_(cameraStatuses),
      sensorStatuses_(sensorStatuses) {

}

std::vector<SolenoidStatus> BoxDeviceStatus::getSolenoidStatusList() const {
  return solenoidStatuses_;
}

std::vector<SensorStatus> BoxDeviceStatus::getSensorStatusList() const {
  return sensorStatuses_;
}

std::vector<CameraStatus> BoxDeviceStatus::getCameraStatusList() const {
  return cameraStatuses_;
}

