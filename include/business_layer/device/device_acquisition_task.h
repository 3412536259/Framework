#pragma once

#include "acquisition_task.h"
#include "solenoid_acquisition_task.h"
#include "sensor_acquisition_task.h"
#include "camera_acquisition_task.h"
#include <vector>
#include <memory>

class DeviceAcquisitionTask {

    public:
        DeviceAcquisitionTask(SolenoidAcquisitionTask& solenoidTask,
                              SensorAcquisitionTask& sensorTask,
                              CameraAcquisitionTask& cameraTask);
        DeviceAcquisitionTask() = default;
        ~DeviceAcquisitionTask();

        const std::vector< std::unique_ptr<AcquisitionTask> >& getTasks() const ;

    private:

        std::vector< std::unique_ptr<AcquisitionTask> > _acquisitionTasks;
};