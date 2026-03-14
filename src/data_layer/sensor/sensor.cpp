#include "sensor.h"

Sensor::Sensor(std::string id,std::string type, std::string port_,
               int baudRate_,std::string parity_,int stopBits_,
               int modbusAddr_,int regStart_,int regCount_ )
    : id(id),type(type),port_(port_),baudRate_(baudRate_),parity_(parity_),stopBits_(stopBits_),
      modbusAddr_(modbusAddr_),regStart_(regStart_),regCount_(regCount_)
{

}

Sensor::~Sensor() {
    
}

SensorStatus Sesnor::getStatus() {

}

SensorRealTimeData Sensor::getRealTimeData() {
    
}