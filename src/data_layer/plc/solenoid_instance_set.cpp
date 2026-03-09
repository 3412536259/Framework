#include "solenoid_instance_set.h"
SolenoidInstanceSet::SolenoidInsatnceSet() {

}

SolenoidInstanceSet::~SolenoidInsatnceSet() {

}

const std::vector<SolenoidStatus>& SolenoidInstanceSet::getSolenoidStatusList() const {
    //循环获取电磁阀状态
}

const std::vector<SolenoidRealTimeData>& SolenoidInstanceSet::getSolenoidRealTimeDataList() const {
    //循环获取电磁阀实时数据
}

int SolenoidInstanceSet::openSolenoidValue(const SolenoidValueInfo& info) {

}

int SolenoidInstanceSet::closeSolenoidValue(const SolenoidValueInfo& info) {
    
}