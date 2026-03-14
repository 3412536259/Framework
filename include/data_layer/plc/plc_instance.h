#ifndef PLC_INSTANCE_H
#define PLC_INSTANCE_H

#include <vector>
#include <unordered_map>
#include "plc_device.h"
#include "solenoid_value.h"
#include "solenoid_value_info.h"
#include "solenoid_status.h"
#include "serial_config.h"
class PlcInstance {
    public:
        PlcInstance() = default;
        PlcInstance(const PlcDevice& plcDevice,
                    const std::vector<SolenoidValue>& solenoidValues);
        ~PlcInstance() = default;

        bool openSolenoidValue(const SolenoidValueInfo& solenoidInfo);
        bool closeSolenoidValue(const SolenoidValueInfo& solenoidInfo);
        SolenoidStatus getSolenoidValueStatus(const SolenoidValueInfo& solenoidInfo);

        //打开串口
        bool connect();
        //关闭串口
        void disconnect();
    
    private:
        //串口配置    
        bool configureSerial();      
        
        //串口文件描述符 前六位计算
        int serialPortStatus_ = -1;    
        PlcDevice plcDevice_;
        SerialConfig serialConfig_;
        //plc下属电磁阀
        std::unordered_map<std::string, SolenoidValue> solenoidMap_;
};

#endif