#ifndef DOOR_LOCK_ACQUISITION_TASK_H
#define DOOR_LOCK_ACQUISITION_TASK_H

#include "acquisition_task.h"
class DoorLockAcquisitionTask : public AcquisitionTask {

    public:
        DoorLockAcquisitionTask(int type, int sampleIntervalSec);
        ~DoorLockAcquisitionTask() override = default;

        bool isAcquisitionData() override;
    
    private:

};

#endif