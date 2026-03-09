#include "box_device_status.h"

BoxDeviceStatus::BoxDeviceStatus(std::vector<SolenoidStatus> solenoidStatuses,
                                 std::vector<CameraStatus> cameraStatuses,
                                 std::vector<SensorStatus> sensorStatuses)
    : solenoidStatuses_(solenoidStatuses),
      cameraStatuses_(cameraStatuses),
      sensorStatuses_(sensorStatuses) {

}

BoxDeviceStatus::BoxDeviceStatus() {

}

BoxDeviceStatus::~BoxDeviceStatus() {

}
