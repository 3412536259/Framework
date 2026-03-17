#include "sensor_status.h"


SensorStatus::SensorStatus(const std::string& deviceId,
                           const int type,
                           const std::string& name,
                           const Status& status) 
    : DeviceStatus(deviceId,type,name),
      status_(status) {

}