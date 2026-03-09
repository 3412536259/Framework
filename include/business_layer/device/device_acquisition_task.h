#pragma once

#include "data_layer/device/acquisition_task.h"
#include "data_layer/plc/solenoid_acquisition_task.h"
#include "data_layer/sensor/sensor_acquisition_task.h"
#include "data_layer/camera/camera_acquisition_task.h"
#include <vector>
#include <memory>

class DeviceAcquisitionTask {

    public:
        DeviceAcquisitionTask(SolenoidAcquisitionTask& solenoidTask,
                              SensorAcquisitionTask& sensorTask,
                              CameraAcquisitionTask& cameraTask);
        ~DeviceAcquisitionTask();

        const std::vector< std::unique_ptr<AcquisitionTask> >& getTasks() const ;

    private:

        std::vector< std::unique_ptr<AcquisitionTask> > _acquisitionTasks;
};