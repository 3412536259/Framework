#include "acquisition_task.h"

AcquisitionTask::AcquisitionTask(int type, int sampleIntervalSec)
    : _type(type), _sampleIntervalSec(sampleIntervalSec)
{

}

AcquisitionTask::~AcquisitionTask() {

}

bool AcquisitionTask::isAcquisitionData()
{
    return true;
}

int AcquisitionTask::getType() const {
    return _type;
}

int AcquisitionTask::getSampleIntervalSec() const {
    return _sampleIntervalSec;
}