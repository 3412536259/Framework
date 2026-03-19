#ifndef WATER_LEVEL_SENSOR_ACQUISITION_TASK_H
#define WATER_LEVEL_SENSOR_ACQUISITION_TASK_H

#include "data_layer/acquisition_task/acquisition_task.h"
class WaterLevelSensorAcquisitionTask : public AcquisitionTask{

    public:
        WaterLevelSensorAcquisitionTask(int type, int sampleIntervalSec);
        ~WaterLevelSensorAcquisitionTask() override = default;
        bool isAcquisitionData() override;
};

#endif