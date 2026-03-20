#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include "data_layer/plc/plc_device.h"
#include "data_layer/plc_device/infrared_sensor_status.h"
class InfraredSensor : public PlcDevice{

    public:
        InfraredSensor() = default;
        InfraredSensor(const int& type,
                       const std::string& deviceId,
                       const std::string& name,
                       const std::string& bindSerialPort,
                       const std::string& slaveAddr,
                       const std::string& plcPort,
                       const std::string& regAddr);
        ~InfraredSensor() override = default;

        std::unique_ptr<DeviceStatus> getStatus() const override;
        InfraredSensorStatus queryStatus(int serialPortStatus);
        

    private:
        std::array<uint8_t,8> buildQueryCommand();
        void splitRegAddress(uint8_t& high,uint8_t& low);
        uint16_t buildCalcCRC(const uint8_t* data,size_t length);
        bool sendData(std::array<uint8_t,8> command,int serialPortStatus);
        int receviceData(unsigned char* recvBuf,int bufSize,int waitTime,int serialPortStatus);
        std::string plcPort_;
        std::string regAddr_;

};

#endif