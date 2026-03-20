#include "business_layer/device/device_acquisition_task.h"
DeviceAcquisitionTask::DeviceAcquisitionTask(const SerialDirectDeviceAcquisitionTask& serialDirectDeviceTask,
                                             const PlcDeviceAcquisitionTask& plcDeviceAcquisitionTask,
                                             const GPIODeviceAcquisitionTask& gpioDeviceAcquisitionTask)
                                             : serialDirectDeviceTask_(serialDirectDeviceTask),
                                               plcDeviceTask_(plcDeviceAcquisitionTask), 
                                               gpioDeviceTask_(gpioDeviceAcquisitionTask){
   
    //配置各种设备的采集任务    
}

DeviceAcquisitionTask::~DeviceAcquisitionTask() {

}

const std::vector< std::unique_ptr<AcquisitionTask> >  DeviceAcquisitionTask::getTasks() const {
    std::vector<std::unique_ptr<AcquisitionTask> > tasks;
    tasks.reserve(20);
    tasks.push_back(std::make_unique<TempHumidSensorAcquisitionTask> ( serialDirectDeviceTask_.getTempHumidSensorTask()) );
    tasks.push_back(std::make_unique<DoorLockAcquisitionTask> (gpioDeviceTask_.getDoorLockTask()) );
    tasks.push_back(std::make_unique<SolenoidAcquisitionTask> (plcDeviceTask_.getSolenoidAcquisitionTask()) );
    tasks.push_back(std::make_unique<InfraredSensorAcquisitionTask> (plcDeviceTask_.getInfraredSensorTask())) ;
    tasks.push_back(std::make_unique<WaterLevelSensorAcquisitionTask> (plcDeviceTask_.getWaterLevelSensorTask())); 
    tasks.push_back(std::make_unique<SmokeDetectorAcquisitionTask> (plcDeviceTask_.getSmokeDetectorTask()));

    return tasks;
}