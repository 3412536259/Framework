#ifndef PLC_INSTANCE_H
#define PLC_INSTANCE_H

#include <vector>
#include <unordered_map>
#include "data_layer/plc/plc_device.h"
#include "data_layer/plc_device/plc_device_info.h"
#include "data_layer/plc_device/solenoid_value.h"
#include "data_layer/plc_device/solenoid_value_info.h"
#include "data_layer/plc_device/solenoid_status.h"
#include "data_layer/serial/serial_config.h"
#include "data_layer/device/device_data.h"
class PlcInstance {
    public:
        PlcInstance(const PlcDevice& plcDevice,
                    const SerialConfig& serialConfig,
                    std::vector<SolenoidValue>& solenoidValues);
        ~PlcInstance() = default;

        bool openSolenoidValue(const PlcDeviceInfo& info);
        bool closeSolenoidValue(const PlcDeviceInfo& info);

        std::vector<SolenoidStatus> getSolenoidStatusList();

        SolenoidStatus getSolenoidValueStatus(const PlcDeviceInfo& info);//获取电磁阀状态

        int getSolenoidSensorNum();

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