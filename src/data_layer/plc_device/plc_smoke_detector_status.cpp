#include "data_layer/plc_device/plc_smoke_detector_status.h"

PlcSmokeDetectorStatus::PlcSmokeDetectorStatus(const std::string& deviceId,
                               const int type,
                               const std::string& name,
                               const SmokeDetectorStatus& status) 
                        : DeviceStatus(deviceId,type,name),
                          status_(status) {

}