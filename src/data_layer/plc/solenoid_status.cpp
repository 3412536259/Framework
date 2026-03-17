#include "solenoid_status.h"

SolenoidStatus::SolenoidStatus(std::string& deviceId,
                               int type,
                               std::string& name,
                               std::string& status,
                               std::string& openStatus)
    : DeviceStatus(deviceId,type,name),
      status_(status),openStatus_(openStatus) {

}

// std::string SolenoidStatus::getStatus() {
//     return status_;
// }

