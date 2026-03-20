#ifndef INFRARED_SENSOR_ACQUISITION_TASK_H
#define INFRARED_SENSOR_ACQUISITION_TASK_H

#include "acquisition_task.h"
class InfraredSensorAcquisitionTask : public AcquisitionTask{

    public:
        InfraredSensorAcquisitionTask(int type, int sampleIntervalSec);
        ~InfraredSensorAcquisitionTask() override = default;
        bool isAcquisitionData() override;
};

#endif