#ifndef SENSOR_ACQUISITION_TASK_H
#define SENSOR_ACQUISITION_TASK_H

#include "acquisition_task.h"

class SensorAcquisitionTask : public AcquisitionTask {
    public:
        SensorAcquisitionTask(int type, int sampleIntervalSec);
        ~SensorAcquisitionTask() override;

        bool isAcquisitionData() override;
    
};

#endif;