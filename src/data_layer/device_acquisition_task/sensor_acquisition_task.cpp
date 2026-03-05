#include "sensor_acquisition_task.h"

SensorAcquisitionTask::SensorAcquisitionTask(int type, int sampleIntervalSec) 
    : AcquisitionTask(type,sampleIntervalSec)
{

}

SensorAcquisitionTask::~SensorAcquisitionTask() {

}

bool SensorAcquisitionTask::isAcquisitionData() {
    return true;

}