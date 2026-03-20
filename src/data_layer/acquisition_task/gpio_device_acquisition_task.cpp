#include "gpio_device_acquisition_task.h"

GPIODeviceAcquisitionTask::GPIODeviceAcquisitionTask(DoorLockAcquisitionTask doorLockTask)
                            : doorLockTask_(doorLockTask) {

}

const DoorLockAcquisitionTask& GPIODeviceAcquisitionTask::getDoorLockTask() const {
    return doorLockTask_;
}