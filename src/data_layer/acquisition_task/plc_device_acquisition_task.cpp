#include "data_layer/acquisition_task/plc_device_acquisition_task.h"

PlcDeviceAcquisitionTask::PlcDeviceAcquisitionTask(const SolenoidAcquisitionTask& solenoidTask,
                                 const InfraredSensorAcquisitionTask& infraredSensorTask,
                                 const WaterLevelSensorAcquisitionTask& waterLevelSensorTask,
                                 const SmokeDetectorAcquisitionTask& smokeDetectorTask) 
                            : solenoidTask_(solenoidTask),
                              infraredSensorTask_(infraredSensorTask),
                              waterLevelSensorTask_(waterLevelSensorTask),
                              smokeDetectorTask_(smokeDetectorTask){

}

const SolenoidAcquisitionTask& PlcDeviceAcquisitionTask::getSolenoidAcquisitionTask() const {
    return solenoidTask_;
}
const InfraredSensorAcquisitionTask& PlcDeviceAcquisitionTask::getInfraredSensorTask() const {
    return infraredSensorTask_;
}
const WaterLevelSensorAcquisitionTask& PlcDeviceAcquisitionTask::getWaterLevelSensorTask() const {
    return waterLevelSensorTask_;
}
const SmokeDetectorAcquisitionTask& PlcDeviceAcquisitionTask::getSmokeDetectorTask() const {
    return smokeDetectorTask_;
}