#include "sensor_status.h"


SensorStatus::SensorStatus(const std::string& deviceId,
                           const int type,
                           const std::string& name,
                           const Status& status,
                           float humidity,
                           float tempature) 
    : DeviceStatus(deviceId,type,name),
      status_(status),
      humidity_(humidity),
      tempature_(tempature) {

}