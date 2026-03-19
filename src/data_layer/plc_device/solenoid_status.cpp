#include "solenoid_status.h"

SolenoidStatus::SolenoidStatus(const std::string& deviceId,
                               const int type,
                               const std::string& name,
                               const std::string& status,
                               const std::string& openStatus)
    : DeviceStatus(deviceId,type,name),
      status_(status),openStatus_(openStatus) {

}

bool SolenoidStatus::isOpen() {
  return openStatus_ == "OPEN";
}

// std::string SolenoidStatus::getStatus() {
//     return status_;
// }

