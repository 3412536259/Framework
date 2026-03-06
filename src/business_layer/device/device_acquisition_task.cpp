#include "device_acquisition_task.h"
DeviceAcquisitionTask::DeviceAcquisitionTask(SolenoidAcquisitionTask& solenoidTask,
                                             SensorAcquisitionTask& sensorTask,
                                             CameraAcquisitionTask& cameraTask){
    _acquisitionTasks.push_back(std::make_unique<SolenoidAcquisitionTask>(solenoidTask));
    _acquisitionTasks.push_back(std::make_unique<SensorAcquisitionTask>(sensorTask));
    _acquisitionTasks.push_back(std::make_unique<CameraAcquisitionTask>(cameraTask));
    //配置各种设备的采集任务    
}

DeviceAcquisitionTask::~DeviceAcquisitionTask() {

}

std::vector< std::unique_ptr<AcquisitionTask> >&  DeviceAcquisitionTask::getTasks() const {
    return _acquisitionTasks;
}