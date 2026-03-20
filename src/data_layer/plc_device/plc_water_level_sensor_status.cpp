#include "data_layer/plc_device/plc_water_level_sensor_status.h"

PlcWaterLevelSensorStatus::PlcWaterLevelSensorStatus(const std::string& deviceId,
                                                     const int type,
                                                     const std::string& name,
                                                     const WaterLevelSensorStatus& status)
    : DeviceStatus(deviceId,type,name ),
      status_(status) {

}