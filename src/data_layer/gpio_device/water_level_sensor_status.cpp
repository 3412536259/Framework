#include "data_layer/gpio_device/water_level_sensor_status.h"

WaterLevelSensorStatus::WaterLevelSensorStatus(const std::string& deviceId,
                                                     const int type,
                                                     const std::string& name,
                                                     const WaterLevelStatus& status)
    : DeviceStatus(deviceId,type,name ),
      status_(status) {

}

std::string WaterLevelSensorStatus::getStatus() {
  switch(status_) {
    case WaterLevelStatus::NORMAL: return "NORMAL";
    case WaterLevelStatus::ABNORMAL: return "ABNORMAL";
    default: return "UNKNOW" ;
  }
}