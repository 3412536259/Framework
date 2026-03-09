#include "sensor_instance_set.h"

SensorInstanceSet::SensorInstanceSet() {

}

SensorInstanceSet::~SensorInstanceSet() {

}

const std::vector<SensorStatus>& SensorInstanceSet::getSensorStatusList() const {
    //循环获取传感器状态
}

const std::vector<SensorRealTimeData>& SensorInstanceSet::getSensorRealTimeDataList() const {
    //循环获取传感器实时数据
}
