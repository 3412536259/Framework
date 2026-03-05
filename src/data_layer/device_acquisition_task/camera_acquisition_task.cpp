#include "camera_acquisition_task.h"

CameraAcquisitionTask::CameraAcquisitionTask(int type, int sampleIntervalSec)
    : AcquisitionTask(type, sampleIntervalSec)
{

}

CameraAcquisitionTask::~CameraAcquisitionTask()
{

}

bool CameraAcquisitionTask::isAcquisitionData()
{
    return true;
}
