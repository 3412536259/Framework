#include "data_layer/gpio_device/smoke_detector_status.h"

SmokeDetectorStatus::SmokeDetectorStatus(const std::string& deviceId,
                               const int type,
                               const std::string& name,
                               const SmokeStatus& status) 
                        : DeviceStatus(deviceId,type,name),
                          status_(status) {

}

std::string SmokeDetectorStatus::getStatus() {
  switch(status_) {
    case SmokeStatus::NORMAL: return "NORMAL";
    case SmokeStatus::ALARM: return "ALARM";
    default: return "UNKNOW" ;
  }
}