#ifndef SOLENOID_STATUS_H
#define SOLENOID_STATUS_H

#include <string>
class SolenoidStatus {

    public:
        SolenoidStatus();
        ~SolenoidStatus();

    private:

        std::string deviceId_;

        //电磁阀状态
        std::string status_;

        
};

#endif