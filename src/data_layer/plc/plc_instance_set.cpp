#include "plc_instance_set.h"

PlcInstanceSet::PlcInstanceSet(const std::unordered_map<std::string,PlcInstance> plcMap) 
    : plcMap_(plcMap) {

}

bool PlcInstanceSet::openPlcSolenoid(const SolenoidValueInfo& info) {


    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return false;
    }
    PlcInstance& plc = it -> second;

    if(!plc.connect()) {
        return false;
    }

    return plc.openSolenoidValue(info);
}

bool PlcInstanceSet::closePlcSolenoid(const SolenoidValueInfo& info) {
    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return false;
    }
    PlcInstance& plc = it -> second;

    if(!plc.disconnect()){
        return false;
    }

    return plc.closeSolenoidValue(info);
}

SolenoidStatus PlcInstanceSet::getPlcSolenoidStatus(const SolenoidValueInfo& info) {
auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return false;
    }
    PlcInstance& plc = it -> second;
    return plc.getSolenoidValueStatus(info);
}