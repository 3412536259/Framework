#ifndef SOLENOID_VALUE_H
#define SOLENOID_VALUE_H

#include <string>
#include "plc_device.h"
#include "solenoid_status.h"
#include "solenoid_real_time_data.h"
class SolenoidValue : public PlcDevice{
    public:
        SolenoidValue();
        SolenoidValue(const int type,
                      const std::string& deviceId,
                      const std::string& name,
                      const std::string& bindSerialPort,
                      const std::string& slaveAddr,
                      const std::string& plcId_,
                      const std::string& plcPort_,
                      const std::string& regAddr_);
        ~SolenoidValue() override = default ;

        //获取电磁阀状态
        SolenoidStatus getStatus() const override;
        std::string getPlcId() const ;
        // SolenoidRealTimeData getRealTimeData();

        bool open(int serialPortStatus);
        bool close(int serialPortStatus);
        SolenoidStatus queryStatus(int serialPortStatus);


    private:
        //指令第3，4字节  plc端口 
        void buildCoilAddress(uint8_t& high,uint8_t& low );    
        //指令7，8字节
        uint16_t buildCalcCRC(const uint8_t* data, size_t length);   

        std::array<unit8_t,8> buildOpenCommand();
        std::Array<uint8_t,8> buildCloseCommand();
    
        std::string plcId_;
        std::string plcPort_;
        // std::string plcSlaveAddr_;
        // std::string type_;
        std::string regAddr_;
};

#endif