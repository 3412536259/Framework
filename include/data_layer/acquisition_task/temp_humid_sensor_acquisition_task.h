#ifndef TEMP_HUMID_SENSOR_ACQUISITION_TASK_H
#define TEMP_HUMID_SENSOR_ACQUISITION_TASK_H

#include "data_layer/acquisition_task/acquisition_task.h"

class TempHumidSensorAcquisitionTask : public AcquisitionTask {
    public:
        TempHumidSensorAcquisitionTask(int type, int sampleIntervalSec);
        ~TempHumidSensorAcquisitionTask() override = default;

        bool isAcquisitionData() override;
    
};

#endif