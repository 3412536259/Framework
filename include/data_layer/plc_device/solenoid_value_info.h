#ifndef SOLENOID_VALUE_INFO_H
#define SOLENOID_VALUE_INFO_H

#include <string>

class SolenoidValueInfo {
    public:
        SolenoidValueInfo() = default;
        SolenoidValueInfo(std::string& plcId,std::string& deviceId);
        ~SolenoidValueInfo() = default;

        const std::string& getDeviceId() const;
        const std::string& getPlcId() const;

    private:
        std::string plcId_;
        std::string deviceId_;

};

#endif