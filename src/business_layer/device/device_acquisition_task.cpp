#include "device_acquisition_task.h"
#include "device_service.h"
DeviceAcquisitionTask::DeviceAcquisitionTask(DeviceService& deviceService)
    : _deviceService(deviceService)
{    
}

DeviceAcquisitionTask::~DeviceAcquisitionTask() {

}

// bool DeviceAcquisitionTask::isAcquisitionSolenoidData() {
//     return _solenoidAcquisitionTask.isAcquisitionData();
// }

// bool DeviceAcquisitionTask::isAcquisitionSensorData() {
//     return _sensorAcquisitionTask.isAcquisitionData();
// }

// bool DeviceAcquisitionTask::isAcuqisitionCameraData() {
//     return _cameraAcquisitionTask.isAcquisitionData();
// }

// SolenoidRealTimeDataList DeviceAcquisitionTask::SolenoidDataAcquisition() {

// }

// SensorRealTimeDataList DeviceAcquisitionTask::SensorDataAcquisition() {

// }

// CameraRealTimeDataList DeviceAcquisitionTask::CameraDataAcquisition() {

// }

std::vector< std::unique_ptr<AcquisitionTask> >&  DeviceAcquisitionTask::getTasks() const {
    return _acquisitionTasks;
}