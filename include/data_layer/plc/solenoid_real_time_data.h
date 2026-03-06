#ifndef SOLENOID_REAL_TIME_DATA_H
#define SOLENOID_REAL_TIME_DATA_H

class SolenoidRealTimeData {
    public:
        SolenoidRealTimeData();
        ~SolenoidRealTimeData();

        bool isOpen();
    private:
        int _openStatus;
};

#endif