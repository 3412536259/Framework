#ifndef PLC_INSTANCE_SET_H
#define PLC_INSTANCE_SET_H


#include "plc_instance.h" 

class PlcInstanceSet {

    public:
        PlcInstanceSet() = default;
        PlcInstanceSet(const std::unordered_map<std::string,PlcInstance> plcMap);
        ~PlcInstanceSet() = default;

        bool openPlcSolenoid(const SolenoidValueInfo& info);
        bool closePlcSolenoid(const SolenoidValueInfo& info);
        SolenoidStatus getPlcSolenoidStatus(const SolenoidValueInfo& info);
    private:
        std::unordered_map<std::string,PlcInstance> plcMap_;
};

#endif