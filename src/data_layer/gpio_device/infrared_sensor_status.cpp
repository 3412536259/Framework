#include "data_layer/gpio_device/infrared_sensor_status.h"

InfraredSensorStatus::InfraredSensorStatus(const std::string& deviceId,
                             const int type,
                             const std::string& name,
                             const InfraredStatus& status) 
                        : DeviceStatus(deviceId,type,name),
                          status_(status) {

}

std::string InfraredSensorStatus::getStatus() {
  switch(status_) {
    case InfraredStatus::NORMAL: return "NORMAL";
    case InfraredStatus::TRIGGER: return "TRIGGER";
    default: return "UNKNOW" ;
  }

}
