#ifndef PLC_INSTANCE_SET_H
#define PLC_INSTANCE_SET_H


#include "data_layer/plc/plc_instance.h" 

class PlcInstanceSet {

    public:
        PlcInstanceSet();
        ~PlcInstanceSet() = default;

        bool openPlcSolenoid(const PlcDeviceInfo& info);
        bool closePlcSolenoid(const PlcDeviceInfo& info);

        std::vector<SolenoidStatus> getPlcSolenoidStatusList();

        std::vector<DeviceData> acquisitionPlcSolenoidData();
        SolenoidStatus getPlcSolenoidStatus(const PlcDeviceInfo& info);
    private:
        std::unordered_map<std::string,PlcInstance> plcMap_;
};

#endif