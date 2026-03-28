#ifndef GPIO_DEVICE_ACQUISITION_TASK_H
#define GPIO_DEVICE_ACQUISITION_TASK_H

#include "data_layer/acquisition_task/door_lock_acquisition_task.h"
#include "data_layer/acquisition_task/infrared_sensor_acquisition_task.h"
#include "data_layer/acquisition_task/water_level_sensor_acquisition_task.h"
#include "data_layer/acquisition_task/smoke_detector_acquisition_task.h"
class GPIODeviceAcquisitionTask {

    public:
        GPIODeviceAcquisitionTask(const DoorLockAcquisitionTask& doorLockTask,
                                 const InfraredSensorAcquisitionTask& infraredSensorTask,
                                 const WaterLevelSensorAcquisitionTask& waterLevelSensorTask,
                                 const SmokeDetectorAcquisitionTask& smokeDetectorTask);
        ~GPIODeviceAcquisitionTask() = default;

        const DoorLockAcquisitionTask& getDoorLockTask() const;
        const InfraredSensorAcquisitionTask& getInfraredSensorTask() const;
        const WaterLevelSensorAcquisitionTask& getWaterLevelSensorTask() const;
        const SmokeDetectorAcquisitionTask& getSmokeDetectorTask() const;
    
    private:
        DoorLockAcquisitionTask doorLockTask_;
        InfraredSensorAcquisitionTask infraredSensorTask_;
        WaterLevelSensorAcquisitionTask waterLevelSensorTask_;
        SmokeDetectorAcquisitionTask smokeDetectorTask_;
};

#endif