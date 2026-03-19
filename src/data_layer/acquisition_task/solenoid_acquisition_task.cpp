#include "data_layer/acquisition_task/solenoid_acquisition_task.h"

SolenoidAcquisitionTask::SolenoidAcquisitionTask(int type, int sampleIntervalSec) 
    : AcquisitionTask(type, sampleIntervalSec)
{
}
SolenoidAcquisitionTask::~SolenoidAcquisitionTask() {

}

bool SolenoidAcquisitionTask::isAcquisitionData() {

    auto now = std::chrono::steady_clock::now();

    if(now >= _nextAcquisitionTime) {
        _nextAcquisitionTime = now + std::chrono::seconds(_sampleIntervalSec);
        return true;
    }
    return false;
}