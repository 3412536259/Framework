#ifndef SERIAL_DIRECT_DEVICE_INFO_H
#define SERIAL_DIRECT_DEVICE_INFO_H

#include <string>
class SerialDirectDeviceInfo {
    public:
        SerialDirectDeviceInfo(std::string& deviceId,
                               int type);
        ~SerialDirectDeviceInfo() = default;
    
        const std::string& getDeviceId() const;
        int getType();
    
    private:
        std::string deviceId_;
        int type_;
};

#endif