#include "data_layer/acquisition_task/smoke_detector_acquisition_task.h"

SmokeDetectorAcquisitionTask::SmokeDetectorAcquisitionTask(int type, int sampleIntervalSec) 
                                : AcquisitionTask(type,sampleIntervalSec){

}

bool SmokeDetectorAcquisitionTask::isAcquisitionData() {
    auto now = std::chrono::steady_clock::now();

    if(now >= _nextAcquisitionTime) {
        _nextAcquisitionTime = now + std::chrono::seconds(_sampleIntervalSec);
        return true;
    }
    return false;
}