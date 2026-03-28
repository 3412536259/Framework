#include "data_layer/serial_direct_device/serial_direct_device_info.h"

SerialDirectDeviceInfo::SerialDirectDeviceInfo(std::string& deviceId,
                               int type)
    : deviceId_(deviceId),
      type_(type) {

}

const std::string& SerialDirectDeviceInfo::getDeviceId() const {
    return deviceId_;
}
int SerialDirectDeviceInfo::getType() {
    return type_;
}