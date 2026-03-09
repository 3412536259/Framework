#include "box_device_real_time_data.h"

BoxDeviceRealTimeData::BoxDeviceRealTimeData(std::vector<SolenoidRealTimeData> solenoidRealTimeDataList,
                                             std::vector<SensorRealTimeData> sensorRealTimeDataList)
    : solenoidRealTimeDataList_(solenoidRealTimeDataList),
      sensorRealTimeDataList_(sensorRealTimeDataList) {

}

BoxDeviceRealTimeData::BoxDeviceRealTimeData() {

}

BoxDeviceRealTimeData::~BoxDeviceRealTimeData() {

}

