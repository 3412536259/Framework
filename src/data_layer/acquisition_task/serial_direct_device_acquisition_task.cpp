#include "serial_direct_device_acquisition_task.h"

SerialDirectDeviceAcquisitionTask::SerialDirectDeviceAcquisitionTask(TempHumidSensorAcquisitionTask tempHumidSensorTask)
                                    : tempHumidSensorTask_(tempHumidSensorTask) {

}

const TempHumidSensorAcquisitionTask& SerialDirectDeviceAcquisitionTask::getTempHumidSensorTask() const {
    return tempHumidSensorTask_;
}