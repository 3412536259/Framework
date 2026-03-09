#ifndef SENSOR_STATUS_H
#define SENSOR_STATUS_H

#include "sensor_types.h"

#include <string>
class SensorStatus {
    public:
        SensorStatus();
        ~SensorStatus();
    
    private:
        
        std::string deviceId;

        Status status;


};

#endif