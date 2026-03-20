#include "data_layer/plc_device/infrared_sensor_status.h"

InfraredSensorStatus::InfraredSensorStatus(const std::string& deviceId,
                             const int type,
                             const std::string& name,
                             const InfraredStatus& status) 
                        : DeviceStatus(deviceId,type,name),
                          status_(status) {

}