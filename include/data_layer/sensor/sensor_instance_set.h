#ifndef SENSOR_INSTANCE_SET_H
#define SENSOR_INSTANCE_SET_H

#include "sensor_status.h"
#include "sensor_real_time_data.h"
#include <sensor.h>

#include <vector>
#include <unordered_map>
#include <memory>
class SensorInstanceSet {
    public:
        SensorInstanceSet() = default;
        ~SensorInstanceSet();

        const std::vector<SensorStatus>& getSensorStatusList() const;
        const std::vector<SensorRealTimeData>& getSensorRealTimeDataList() const;

    private:
        std::unordered_map<std::string,std::unique_ptr<Sensor> > _sensors;
};

#endif