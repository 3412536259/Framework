#include "data_layer/plc/plc_instance_set.h"

PlcInstanceSet::PlcInstanceSet(const std::unordered_map<std::string,PlcInstance> plcMap) 
    : plcMap_(plcMap) {

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
        const auto& list = plc.getInfraredSensorStatusList();
        solenoidStatusList.insert(solenoidStatusList.end(),list.begin(),list.end());
    }
    return solenoidStatusList;
}

std::vector<InfraredSensorStatus> PlcInstanceSet::getPlcInfraredSensorStatusList() {
    std::vector<InfraredSensorStatus> infraredStatusList;
    int listSize = 0;
    for( auto& [key,plc] : plcMap_) {
        listSize += plc.getInfraredSensorNum(); 
    }
    infraredStatusList.reserve(listSize);
    for(auto& [key,plc] : plcMap_) {
        const auto& list = plc.getInfraredSensorStatusList();
        infraredStatusList.insert(infraredStatusList.end(),list.begin(),list.end());
    }
    return infraredStatusList;
}
std::vector<PlcSmokeDetectorStatus> PlcInstanceSet::getPlcSmokeDetectorStatusList() {
    std::vector<PlcSmokeDetectorStatus> smokeStatusList;
    int listSize = 0;
    for(auto& [key,plc] : plcMap_) {
        listSize += plc.getSmokeSensorNum(); 
    }
    smokeStatusList.reserve(listSize);
    for(auto& [key,plc] : plcMap_) {
        const auto& list = plc.getSmokeDetectorStatusList();
        smokeStatusList.insert(smokeStatusList.end(),list.begin(),list.end());
    }
    return smokeStatusList;
}
std::vector<PlcWaterLevelSensorStatus> PlcInstanceSet::getPlcWaterLevelSensorStatusList() {
    std::vector<PlcWaterLevelSensorStatus> waterLevelSensorStatusList;
    int listSize = 0;
    for(auto& [key,plc] : plcMap_) {
        listSize += plc.getWaterLevelSensorNum(); 
    }
    waterLevelSensorStatusList.reserve(listSize);
    for( auto& [key,plc] : plcMap_) {
        const auto& list = plc.getWaterLevelStatusList();
        waterLevelSensorStatusList.insert(waterLevelSensorStatusList.end(),list.begin(),list.end());
    }
    return waterLevelSensorStatusList;
}

std::vector<std::unique_ptr<DeviceData> > PlcInstanceSet::acquisitionPlcSolenoidData() {
    std::vector<std::unique_ptr<DeviceData> > solenoidDataList;
    int listSize = 0;
    for(auto& [key,plc] : plcMap_) {
        listSize += plc.getSolenoidSensorNum(); 
    }

    for( auto& [key,plc] : plcMap_) {
        std::vector<SolenoidStatus> statusList = plc.getSolenoidStatusList();

        for (auto& status : statusList) {
            solenoidDataList.push_back( std::make_unique<DeviceData>(0, status) );
        }
    }
}
std::vector<std::unique_ptr<DeviceData> > PlcInstanceSet::acquisitionPlcInfraredSensorData() {
    std::vector<std::unique_ptr<DeviceData> > infraredDataList;
    int listSize = 0;
    for(auto& [key,plc] : plcMap_) {
        listSize += plc.getInfraredSensorNum(); 
    }

    for( auto& [key,plc] : plcMap_) {
        std::vector<InfraredSensorStatus> statusList = plc.getInfraredSensorStatusList();

        for (auto& status : statusList) {
            infraredDataList.push_back( std::make_unique<DeviceData>(4, status) );
        }
    }
}
std::vector<std::unique_ptr<DeviceData> > PlcInstanceSet::acquisitionPlcSmokeDetectorData() {
    std::vector<std::unique_ptr<DeviceData> > smokeDetectorDataList;
    int listSize = 0;
    for(auto& [key,plc] : plcMap_) {
        listSize += plc.getSmokeSensorNum(); 
    }

    for( auto& [key,plc] : plcMap_) {
        std::vector<PlcSmokeDetectorStatus> statusList = plc.getSmokeDetectorStatusList();

        for (auto& status : statusList) {
            smokeDetectorDataList.push_back( std::make_unique<DeviceData>(5, status) );
        }
    }
}
std::vector<std::unique_ptr<DeviceData> > PlcInstanceSet::acquisitionPlcWaterLevelSensorData() {
    std::vector<std::unique_ptr<DeviceData> > waterLevelSensorDataList;
    int listSize = 0;
    for(auto& [key,plc] : plcMap_) {
        listSize += plc.getSolenoidSensorNum(); 
    }

    for( auto& [key,plc] : plcMap_) {
        std::vector<PlcWaterLevelSensorStatus> statusList = plc.getWaterLevelStatusList();

        for (auto& status : statusList) {
            waterLevelSensorDataList.push_back( std::make_unique<DeviceData>(6, status) );
        }
    }
}

SolenoidStatus PlcInstanceSet::getPlcSolenoidStatus(const SolenoidValueInfo& info) {
    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return SolenoidStatus();
    }
    PlcInstance& plc = it -> second;
    return plc.getSolenoidValueStatus(info);
}

InfraredSensorStatus PlcInstanceSet::getPlcInfraredSensorStatus(const PlcDeviceInfo& info) {
    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return InfraredSensorStatus();
    }
    PlcInstance& plc = it -> second;
    return plc.getInfraredSensorStatus(info);
}
PlcSmokeDetectorStatus PlcInstanceSet::getPlcSmokeDetectorStatus(const PlcDeviceInfo& info) {
    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return PlcSmokeDetectorStatus();
    }
    PlcInstance& plc = it -> second;
    return plc.getSmokeDetectorStatus(info);
}
PlcWaterLevelSensorStatus PlcInstanceSet::getPlcWaterLevelSensorStatus(const PlcDeviceInfo& info) {
    auto it = plcMap_.find(info.getPlcId());

    if(it == plcMap_.end()) {
        return PlcWaterLevelSensorStatus();
    }
    PlcInstance& plc = it -> second;
    return plc.getWaterLevelSensorStatus(info);
}