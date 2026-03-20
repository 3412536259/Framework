#ifndef GPIO_DEVICE_ACQUISITION_TASK_H
#define GPIO_DEVICE_ACQUISITION_TASK_H

#include "door_lock_acquisition_task.h"
class GPIODeviceAcquisitionTask {

    public:
        GPIODeviceAcquisitionTask(DoorLockAcquisitionTask doorLockTask);
        ~GPIODeviceAcquisitionTask() = default;

        const DoorLockAcquisitionTask& getDoorLockTask() const;
    
    private:
        DoorLockAcquisitionTask doorLockTask_;
};

#endif