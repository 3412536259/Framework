#include "data_layer/plc/plc_instance_set.h"

PlcInstanceSet::PlcInstanceSet() 
{

}

bool PlcInstanceSet::openPlcSolenoid(const PlcDeviceInfo& info) {
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

bool PlcInstanceSet::closePlcSolenoid(const PlcDeviceInfo& info) {
    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return false;
    }
    PlcInstance& plc = it -> second;

    if(!plc.connect()){
        return false;
    }

    return plc.closeSolenoidValue(info);
}
std::vector<SolenoidStatus> PlcInstanceSet::getPlcSolenoidStatusList() {
    std::vector<SolenoidStatus> solenoidStatusList;
    int listSize = 0;
    for( auto& [key,plc] : plcMap_) {
        listSize += plc.getSolenoidSensorNum(); 
    }
    solenoidStatusList.reserve(listSize);
    for( auto& [key,plc] : plcMap_) {
        const auto& list = plc.getSolenoidStatusList();
        solenoidStatusList.insert(solenoidStatusList.end(),list.begin(),list.end());
    }
    return solenoidStatusList;
}

std::vector<DeviceData> PlcInstanceSet::acquisitionPlcSolenoidData() {
    std::vector<DeviceData> solenoidDataList;
    int listSize = 0;
    for(auto& [key,plc] : plcMap_) {
        listSize += plc.getSolenoidSensorNum(); 
    }

    for( auto& [key,plc] : plcMap_) {
        std::vector<SolenoidStatus> statusList = plc.getSolenoidStatusList();

        for (auto& status : statusList) {
            solenoidDataList.push_back( DeviceData(0, status) );
        }
    }
    return solenoidDataList;
}

SolenoidStatus PlcInstanceSet::getPlcSolenoidStatus(const PlcDeviceInfo& info) {
    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return SolenoidStatus();
    }
    PlcInstance& plc = it -> second;
    return plc.getSolenoidValueStatus(info);
}
