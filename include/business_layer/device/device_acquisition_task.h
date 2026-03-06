#pragma once

#include "acquisition_task.h"
#include "device_service.h"

class DeviceAcquisitionTask {

    public:
        DeviceAcquisitionTask(DeviceService& deviceService);
        ~DeviceAcquisitionTask();

        // SolenoidRealTimeDataList SolenoidDataAcquisition();
        // SensorRealTimeDataList SensorDataAcquisition();
        // CameraRealTimeDataList CameraDataAcquisition();

        const std::vector< std::unique_ptr<AcquisitionTask> >& getTasks() const ;

    private:

        std::vector< std::unique_ptr<AcquisitionTask> > _acquisitionTasks;

        DeviceService& _deviceService;

};