#ifndef SENSOR_H
#define SENSOR_H

#include <string>
class Sensor {  
    public:
        Sensor() = default;
        ~Sensor();

    private:
        std::string id;
        std::string name;
        int type;

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