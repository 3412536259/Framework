#ifndef PLC_DEVICE_ACQUISITION_TASK_H
#define PLC_DEVICE_ACQUISITION_TASK_H

#include "data_layer/acquisition_task/solenoid_acquisition_task.h"

class PlcDeviceAcquisitionTask {

    public:
        PlcDeviceAcquisitionTask(const SolenoidAcquisitionTask& solenoidTask);
        ~PlcDeviceAcquisitionTask() = default;

        const SolenoidAcquisitionTask& getSolenoidAcquisitionTask() const;
       
    
    private:
        SolenoidAcquisitionTask solenoidTask_;
        


};

#endif