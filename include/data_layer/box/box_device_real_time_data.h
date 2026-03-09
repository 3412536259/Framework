#ifndef BOX_DEVICE_REAL_TIME_DATA_H
#define BOX_DEVICE_REAL_TIME_DATA_H

#include <vector>
#include "solenoid_real_time_data.h"
#include "sensor_real_time_data.h"
class BoxDeviceRealTimeData {
    public:
        BoxDeviceRealTimeData(std::vector<SolenoidRealTimeData> solenoidRealTimeDataList,
                              std::vector<SensorRealTimeData> sensorRealTimeDataList);
        BoxDeviceRealTimeData() = default;
        ~BoxDeviceRealTimeData();

    private:
        std::vector<SolenoidRealTimeData> solenoidRealTimeDataList_;
        std::vector<SensorRealTimeData> sensorRealTimeDataList_;
};


#endif