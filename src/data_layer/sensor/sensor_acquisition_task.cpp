#include "sensor_acquisition_task.h"

SensorAcquisitionTask::SensorAcquisitionTask(int type, int sampleIntervalSec) 
    : AcquisitionTask(type,sampleIntervalSec)
{
    _nextAcquisitionTime = std::chrono::steady_clock::now();
}

SensorAcquisitionTask::~SensorAcquisitionTask() {

}

bool SensorAcquisitionTask::isAcquisitionData() {
    auto now = std::chrono::steady_clock::now();
    if(now >= _nextAcquisitionTime) {
        _nextAcquisitionTime = now + _sampleIntervalSec;
        return true;
    }
    return false;

}