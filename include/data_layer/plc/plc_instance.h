#ifndef PLC_INSTANCE_H
#define PLC_INSTANCE_H

#include <vector>
#include <unordered_map>
#include "data_layer/plc/plc_device.h"
#include "data_layer/plc_device/plc_device_info.h"
#include "data_layer/plc_device/solenoid_value.h"
#include "data_layer/plc_device/infrared_sensor.h"
#include "data_layer/plc_device/plc_smoke_detector.h"
#include "data_layer/plc_device/plc_water_level_sensor.h"
#include "data_layer/plc_device/solenoid_value_info.h"
#include "data_layer/plc_device/solenoid_status.h"
#include "data_layer/plc_device/infrared_sensor_status.h"
#include "data_layer/plc_device/plc_smoke_detector_status.h"
#include "data_layer/plc_device/plc_water_level_sensor_status.h"
#include "data_layer/serial/serial_config.h"
#include "data_layer/device/device_data.h"
class PlcInstance {
    public:
        PlcInstance() = default;
        PlcInstance(const PlcDevice& plcDevice,
                    const SerialConfig& serialConfig,
                    const std::vector<SolenoidValue>& solenoidValues,
                    const std::vector<InfraredSensor>& infraredSensors,
                    const std::vector<PlcSmokeDetector>& smokeDetectors,
                    const std::vector<PlcWaterLevelSensor>& waterLevelSensors);
        ~PlcInstance() = default;

        bool openSolenoidValue(const PlcDeviceInfo& info);
        bool closeSolenoidValue(const PlcDeviceInfo& info);

        std::vector<SolenoidStatus> getSolenoidStatusList();
        std::vector<InfraredSensorStatus> getInfraredSensorStatusList();
        std::vector<PlcSmokeDetectorStatus> getSmokeDetectorStatusList();
        std::vector<PlcWaterLevelSensorStatus> getWaterLevelStatusList();

        SolenoidStatus getSolenoidValueStatus(const SolenoidValueInfo& info);//获取电磁阀状态
        InfraredSensorStatus getInfraredSensorStatus(const PlcDeviceInfo& info);//获取红外传感器状态
        PlcSmokeDetectorStatus getSmokeDetectorStatus(const PlcDeviceInfo& info);//获取烟感传感器状态
        PlcWaterLevelSensorStatus getWaterLevelSensorStatus(const PlcDeviceInfo& info);//获取水浸传感器状态

        int getSolenoidSensorNum();
        int getInfraredSensorNum();
        int getSmokeSensorNum();
        int getWaterLevelSensorNum();

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
        std::unordered_map<std::string, InfraredSensor> infraredSensorMap_;
        std::unordered_map<std::string, PlcSmokeDetector> smokeDetectorMap_;
        std::unordered_map<std::string, PlcWaterLevelSensor> waterLevelSensorMap_;
};

#endif