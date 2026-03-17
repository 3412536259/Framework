#ifndef SENSOR_H
#define SENSOR_H

#include "sensor_status.h"
#include "sensor_real_time_data.h"

#include <string>
class Sensor {  
    public:
        Sensor() = default;
        Sensor(std::string id,std::string type, std::string port_,
               int baudRate_,std::string parity_,int stopBits_,
               int modbusAddr_,int regStart_,int regCount_ );
        ~Sensor();

        SensorStatus getStatus();
        SensorRealTimeData getRealTimeData();

    private:
        std::string id;
        std::string name;
        std::string type;

        //SerialConfig
        std::string port_;
        int baudRate_;
        std::string parity_;
        int stopBits_;

        int modbusAddr_;
        int regStart_;
        int regCount_;
};

#endif