#ifndef DEVICE_STATUS_H
#define DEVICE_STATUS_H

#include <string>
class DeviceStatus {

    protected:
        DevcieStatus() : type_(0) {}
        DeviceStatus(const std::string& deviceId,
                     const int type,
                     const std::string& name);

    public:
        virtual ~DeviceStatus() = default;

        int getType() {return type_;}
    
    private:
        std::string deviceId_;
        int type_;
        std::string name_;
};

#endif