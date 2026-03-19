#ifndef PLC_WATER_LEVEL_SENSOR_H
#define PLC_WATER_LEVEL_SENSOR_H

#include "plc_device.h"
#include "plc_water_level_sensor_status.h"
class PlcWaterLevelSensor : public PlcDevice {
    public:
        PlcWaterLevelSensor();
        PlcWaterLevelSensor(const int& type,
                            const std::string& deviceId,
                            const std::string& name,
                            const std::string& bindSerialPort,
                            const std::string& slaveAddr,
                            const std::string& plcPort,
                            const std::string& regAddr);
        ~PlcWaterLevelSensor() override = default;

        std::unique_ptr<DeviceStatus> getStatus() const override ;

        PlcWaterLevelSensorStatus queryStatus(int serialPortStatus);
    
    private:
        std::array<uint8_t,8> buildQueryCommand();
        void splitRegAddress(uint8_t& high,uint8_t& low);
        uint16_t buildCalcCRC(const uint8_t* data,size_t length);
        bool sendData(std::array<uint8_t,8> command,int serialPortStatus);
        int receviceData(unsigned char* recvBuf,int bufSize,int waitTime, int serialPortStatus);
        
        std::string plcPort_;
        std::string regAddr_;
};

#endif