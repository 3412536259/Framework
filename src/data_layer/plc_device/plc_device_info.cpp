#include "data_layer/plc_device/plc_device_info.h"
#include "business_layer/lobby/lobby_object.h"
PlcDeviceInfo::PlcDeviceInfo(const std::string& plcId,
                             const std::string& deviceId)
                            : plcId_(plcId),
                              deviceId_(deviceId) {

} 

const std::string& PlcDeviceInfo::getPlcId() const {
    return plcId_;
}

const std::string& PlcDeviceInfo::getDeviceId() const {
    return deviceId_;
}

PlcDeviceInfo PlcDeviceInfo::createPlcDevice(const SolenoidValveOperation& op){
    return PlcDeviceInfo(op.getDeviceId(),op.getPlcId());
}