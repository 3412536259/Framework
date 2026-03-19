#include "data_layer/plc_device/plc_device_info.h"

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