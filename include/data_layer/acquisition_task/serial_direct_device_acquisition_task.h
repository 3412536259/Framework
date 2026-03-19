#ifndef SERIAL_DIRECT_DEVICE_ACQUISITION_TASK_H
#define SERIAL_DIRECT_DEVICE_ACQUISITION_TASK_H

#include "data_layer/acquisition_task/temp_humid_sensor_acquisition_task.h"
class SerialDirectDeviceAcquisitionTask {

    public:
        SerialDirectDeviceAcquisitionTask(TempHumidSensorAcquisitionTask tempHumidSensorTask);
        ~SerialDirectDeviceAcquisitionTask() = default;

        const TempHumidSensorAcquisitionTask& getTempHumidSensorTask() const;
    
    private:
        TempHumidSensorAcquisitionTask tempHumidSensorTask_;
};

#endif