#include "data_layer/acquisition_task/gpio_device_acquisition_task.h"

GPIODeviceAcquisitionTask::GPIODeviceAcquisitionTask(const DoorLockAcquisitionTask& doorLockTask,
                                 const InfraredSensorAcquisitionTask& infraredSensorTask,
                                 const WaterLevelSensorAcquisitionTask& waterLevelSensorTask,
                                 const SmokeDetectorAcquisitionTask& smokeDetectorTask)
                            : doorLockTask_(doorLockTask),
                              infraredSensorTask_(infraredSensorTask),
                              waterLevelSensorTask_(waterLevelSensorTask),
                              smokeDetectorTask_(smokeDetectorTask) {

}

const DoorLockAcquisitionTask& GPIODeviceAcquisitionTask::getDoorLockTask() const {
    return doorLockTask_;
}
const InfraredSensorAcquisitionTask& GPIODeviceAcquisitionTask::getInfraredSensorTask() const {
    return infraredSensorTask_;
}
const WaterLevelSensorAcquisitionTask& GPIODeviceAcquisitionTask::getWaterLevelSensorTask() const {
    return waterLevelSensorTask_;
}
const SmokeDetectorAcquisitionTask& GPIODeviceAcquisitionTask::getSmokeDetectorTask() const {
    return smokeDetectorTask_;
}