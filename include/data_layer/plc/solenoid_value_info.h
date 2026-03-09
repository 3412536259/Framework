#ifndef SOLENOID_VALUE_INFO_H
#define SOLENOID_VALUE_INFO_H

#include <string>

class SolenoidValueInfo {
    public:
        SolenoidValueInfo();
        SolenoidValueInfo(std::string deviceId);
        ~SolenoidValueInfo(); 

        const std::string getDeviceId() const;

    private:
        std::string deviceId_;

};

#endif