#ifndef SENSOR_INSTANCE_SET_H
#define SENSOR_INSTANCE_SET_H

#include "sensor_status.h"
#include "sensor_real_time_data.h"
#include "data_layer/sensor/sensor.h"

#include <vector>
#include <unordered_map>
#include <memory>
class SensorInstanceSet {
    public:
        SensorInstanceSet() = default;
        ~SensorInstanceSet();

        const std::vector<SensorStatus>& getSensorStatusList() const;
         //循环获取传感器实时数据
        const std::vector<SensorRealTimeData>& getSensorRealTimeDataList() const;

        std::vector<std::unique_ptr<DeviceData> > acquisitionSensorData();

    private:
        std::unordered_map<std::string,std::unique_ptr<Sensor> > sensors_;
};

#endif