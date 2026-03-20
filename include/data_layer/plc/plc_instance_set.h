#ifndef PLC_INSTANCE_SET_H
#define PLC_INSTANCE_SET_H


#include "data_layer/plc/plc_instance.h" 

class PlcInstanceSet {

    public:
        PlcInstanceSet() = default;
        PlcInstanceSet(const std::unordered_map<std::string,PlcInstance> plcMap);
        ~PlcInstanceSet() = default;

        bool openPlcSolenoid(const PlcDeviceInfo& info);
        bool closePlcSolenoid(const PlcDeviceInfo& info);

        std::vector<SolenoidStatus> getPlcSolenoidStatusList();
        std::vector<InfraredSensorStatus> getPlcInfraredSensorStatusList();
        std::vector<PlcSmokeDetectorStatus> getPlcSmokeDetectorStatusList();
        std::vector<PlcWaterLevelSensorStatus> getPlcWaterLevelSensorStatusList();

        std::vector<std::unique_ptr<DeviceData> > acquisitionPlcSolenoidData();
        std::vector<std::unique_ptr<DeviceData> > acquisitionPlcInfraredSensorData();
        std::vector<std::unique_ptr<DeviceData> > acquisitionPlcSmokeDetectorData();
        std::vector<std::unique_ptr<DeviceData> > acquisitionPlcWaterLevelSensorData();

        SolenoidStatus getPlcSolenoidStatus(const SolenoidValueInfo& info);
        InfraredSensorStatus getPlcInfraredSensorStatus(const PlcDeviceInfo& info);//获取红外传感器状态
        PlcSmokeDetectorStatus getPlcSmokeDetectorStatus(const PlcDeviceInfo& info);//获取烟感传感器状态
        PlcWaterLevelSensorStatus getPlcWaterLevelSensorStatus(const PlcDeviceInfo& info);//获取水浸传感器状态
    private:
        std::unordered_map<std::string,PlcInstance> plcMap_;
};

#endif