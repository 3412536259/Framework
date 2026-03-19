#ifndef SOLENOID_STATUS_H
#define SOLENOID_STATUS_H

#include <string>
#include "data_layer/device/device_status.h"
class SolenoidStatus : public DeviceStatus{

    public:
        SolenoidStatus(const std::string& deviceId,
                       const int type,
                       const std::string& name,
                       const std::string& status,
                       const std::string& openStatus);
        SolenoidStatus() = default;
        ~SolenoidStatus() override = default;

        bool isOpen();
        // std::string getStatus() const;

    private:
        //寄存器地址
        // std::string registerAddress_;

        //电磁阀状态
        std::string status_;

        std::string openStatus_;
};

#endif