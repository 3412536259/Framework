#ifndef SMOKE_DETECTOR_ACQUISITION_TASK_H
#define SMOKE_DETECTOR_ACQUISITION_TASK_H

#include "data_layer/acquisition_task/acquisition_task.h"
class SmokeDetectorAcquisitionTask : public AcquisitionTask{

    public:
        SmokeDetectorAcquisitionTask(int type, int sampleIntervalSec);
        ~SmokeDetectorAcquisitionTask() override = default;
        bool isAcquisitionData() override;
};

#endif