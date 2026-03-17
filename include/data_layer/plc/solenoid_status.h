#ifndef SOLENOID_STATUS_H
#define SOLENOID_STATUS_H

#include <string>
#include "device_status.h"
class SolenoidStatus : public DeviceStatus{

    public:
        SolenoidStatus(std::string& deviceId,
                       int type,
                       std::string& name,
                       std::string& status,
                       std::string& openStatus);
        SolenoidStatus() = default;
        ~SolenoidStatus() override = default;

        // std::string getStatus() const;

    private:
        //寄存器地址
        // std::string registerAddress_;

        //电磁阀状态
        std::string status_;

        std::string openStatus_;
};

#endif