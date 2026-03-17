#include "solenoid_instance_set.h"
SolenoidInstanceSet::SolenoidInsatnceSet(const std::unordered_map<std::string, std::unique_ptr<SolenoidValue> >& solenoidValues) 
    :solenoidValues_(solenoidValues)
{

}

SolenoidInstanceSet::~SolenoidInstanceSet() {

}

const std::vector<SolenoidStatus> SolenoidInstanceSet::getSolenoidStatusList() const {
    std::vector<SolenoidStatus> solenoidStatusList;
    solenoidStatusList.reserve(solenoidValues_.size());
    for(const auto& [key, solenoid] : solenoidValues_) {
        solenoidStatusList.push_back(solenoid->getStatus());
    }
    return solenoidStatusList;
}

const std::vector<SolenoidRealTimeData> SolenoidInstanceSet::getSolenoidRealTimeDataList() const {
    std::vector<SolenoidRealTimeData> realTimeDataList;
    realTimeDataList.reserve(solenoidValues_.size());
    for(const auto& [key,solenoid] : solenoidValue_) {
        realTimeDataList.push_back(solenoid->getRealTimeData());
    }
    return realTimeDataList;
}

std::vector<std::unique_ptr<DeviceData> > SolenoidInstanceSet::acquisitionSolenoidData() {
    std::vector<std::unique_ptr<DeviceData> > deviceDataList;
    deviceDataList.reserve(solenoidValues_.size());
    for(const auto& [key,solenoid] : solenoidValues_) {
        deviceDataList.push_back(std::make_unique<DeviceData>(0,solenoid->getStatus(),solenoid->getRealTimeData()));
    }
    return deviceDataList;
}


int SolenoidInstanceSet::openSolenoidValue(const SolenoidValueInfo& info) {
    auto solenoid = solenoidValues_.find(info.getDeviceId());
    if(solenoid == solenoidValues_.end()) {
        return -1; //电磁阀不存在
    }
    if(solenoid -> open() ) return 0;
    return 1;
}

int SolenoidInstanceSet::closeSolenoidValue(const SolenoidValueInfo& info) {
    auto solenoid = solenoidValues_.find(info.getDeviceId());
    if(solenoid == solenoidValues_.end()) return -1;//电磁阀不存在
    if(solenoid -> close() ) return 0;
    return 1;
}