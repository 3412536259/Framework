#include "data_layer/acquisition_task/water_level_sensor_acquisition_task.h"


WaterLevelSensorAcquisitionTask::WaterLevelSensorAcquisitionTask(int type, int sampleIntervalSec) 
                                : AcquisitionTask(type,sampleIntervalSec){

}
bool WaterLevelSensorAcquisitionTask::isAcquisitionData()  {
    auto now = std::chrono::steady_clock::now();

    if(now >= _nextAcquisitionTime) {
        _nextAcquisitionTime = now + std::chrono::seconds(_sampleIntervalSec);
        return true;
    }
    return false;
}
