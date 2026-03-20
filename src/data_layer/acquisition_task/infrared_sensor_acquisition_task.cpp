#include "infrared_sensor_acquisition_task.h"

InfraredSensorAcquisitionTask::InfraredSensorAcquisitionTask(int type, int sampleIntervalSec) 
                                : AcquisitionTask(type,sampleIntervalSec){

}
bool InfraredSensorAcquisitionTask::isAcquisitionData()  {
    auto now = std::chrono::steady_clock::now();

    if(now >= _nextAcquisitionTime) {
        _nextAcquisitionTime = now + std::chrono::seconds(_sampleIntervalSec);
        return true;
    }
    return false;
}
