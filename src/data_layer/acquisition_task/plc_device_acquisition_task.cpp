#include "data_layer/acquisition_task/plc_device_acquisition_task.h"

PlcDeviceAcquisitionTask::PlcDeviceAcquisitionTask(const SolenoidAcquisitionTask& solenoidTask) 
                            : solenoidTask_(solenoidTask){

}

const SolenoidAcquisitionTask& PlcDeviceAcquisitionTask::getSolenoidAcquisitionTask() const {
    return solenoidTask_;
}
