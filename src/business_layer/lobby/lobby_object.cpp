#include "business_layer/lobby/lobby_object.h"

SolenoidValveOperation::SolenoidValveOperation(const json& j){
        deviceId  = j.value("deviceId", "");
        cmd       = j.value("cmd", "");
        plcId     = j.value("plcId", "");
        reqSource = j.value("reqSource", "");
}


const std::string& SolenoidValveOperation::getDeviceId() const{
    return deviceId;
}
const std::string& SolenoidValveOperation::getCmd() const{
    return cmd;
}
const std::string& SolenoidValveOperation::getPlcId() const{
    return plcId;
}

const std::string& SolenoidValveOperation::getReqSource() const{
    return reqSource;
}
bool SolenoidValveOperation::isValid() {
    // 简单判空，你可以按需求改
    return !deviceId.empty() && !cmd.empty() && !plcId.empty();
}