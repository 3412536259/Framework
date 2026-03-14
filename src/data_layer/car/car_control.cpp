#include "car_control.h"

CarControl::CarControl(const std::string& deviceId) const : deviceId_(deviceId) {

}

const std::string& CarControl::getDeviceId() const {
    return deviceId_;
} 