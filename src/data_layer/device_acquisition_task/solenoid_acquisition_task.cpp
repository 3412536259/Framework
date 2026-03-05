#include "solenoid_acquisition_task.h"

SolenoidAcquisitionTask::SolenoidAcquisitionTask(int type, int sampleIntervalSec) 
    : AcquisitionTask(type, sampleIntervalSec)
{

}
SolenoidAcquisitionTask::~SolenoidAcquisitionTask() {

}

bool SolenoidAcquisitionTask::isAcquisitionData() {
    
    return true;
}