#ifndef PLC_DEVICE_ACQUISITION_TASK_H
#define PLC_DEVICE_ACQUISITION_TASK_H

#include "data_layer/acquisition_task/solenoid_acquisition_task.h"
#include "data_layer/acquisition_task/infrared_sensor_acquisition_task.h"
#include "data_layer/acquisition_task/water_level_sensor_acquisition_task.h"
#include "data_layer/acquisition_task/smoke_detector_acquisition_task.h"
class PlcDeviceAcquisitionTask {

    public:
        PlcDeviceAcquisitionTask(const SolenoidAcquisitionTask& solenoidTask,
                                 const InfraredSensorAcquisitionTask& infraredSensorTask,
                                 const WaterLevelSensorAcquisitionTask& waterLevelSensorTask,
                                 const SmokeDetectorAcquisitionTask& smokeDetectorTask);
        ~PlcDeviceAcquisitionTask() = default;

        const SolenoidAcquisitionTask& getSolenoidAcquisitionTask() const;
        const InfraredSensorAcquisitionTask& getInfraredSensorTask() const;
        const WaterLevelSensorAcquisitionTask& getWaterLevelSensorTask() const;
        const SmokeDetectorAcquisitionTask& getSmokeDetectorTask() const;
    
    private:
        SolenoidAcquisitionTask solenoidTask_;
        InfraredSensorAcquisitionTask infraredSensorTask_;
        WaterLevelSensorAcquisitionTask waterLevelSensorTask_;
        SmokeDetectorAcquisitionTask smokeDetectorTask_;


};

#endif