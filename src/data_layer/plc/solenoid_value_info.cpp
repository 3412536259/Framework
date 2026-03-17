#include "solenoid_value_info.h"


SolenoidValueInfo::SolenoidValueInfo(std::string& plcId,std::string& deviceId)
    :   plcId_(plcId)
        deviceId_(deviceId){
    
}

const std::string& SolenoidValueInfo::getDeviceId() const {
    return deviceId_;
}

const std::string& SolenoidValueInfo::getPlcId() const {
    return plcId_;
}