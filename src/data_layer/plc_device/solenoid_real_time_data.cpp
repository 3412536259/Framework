#include "solenoid_real_time_data.h"

SolenoidRealTimeData::SolenoidRealTimeData() {

}

SolenoidRealTimeData::~SolenoidRealTimeData() {

}

bool SolenoidRealTimeData::isOpen() {
    return openStatus_ == 1;
}