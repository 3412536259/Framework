#include "solenoid_value_info.h"

SolenoidValueInfo::SolenoidValueInfo() {

}

SolenoidValueInfo::SolenoidValueInfo(std::string deviceId): deviceId_(deviceId) {
    
}

SolenoidValueInfo::~SolenoidValueInfo() {

}

const std::string SolenoidValueInfo::getDeviceId() const {
    return deviceId_;
}