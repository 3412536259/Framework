#include "data_layer/serial_direct_device/serial_direct_device_instance_set.h"

SerialDirectDeviceInstanceSet::SerialDirectDeviceInstanceSet() {
    auto& config = ConfigParser::getInstance().getConfig();

    for(auto& sensor : config.sensors) {
        TempHumidSensor s = TempHumidSensor(1,sensor.id,sensor.name,sensor.serial.port,
                                            sensor.slaveAddr,sensor.regAddr,sensor.readRegs,
                                            SerialConfig(sensor.serial.baudRate,8,sensor.serial.stopBits,
                                                        sensor.serial.parity));
        if(sensors_.count(sensor.id)) continue;
        sensors_.emplace(sensor.id,s);
    }
}

std::vector<TempHumidSensorStatus> SerialDirectDeviceInstanceSet::getSensorStatusList() {
    std::vector<TempHumidSensorStatus> statusList;
    statusList.reserve(sensors_.size());

    for(auto& [key, sensor] : sensors_) {
        statusList.push_back(sensor.readSensorData());
    }

    return statusList;
}

TempHumidSensorStatus SerialDirectDeviceInstanceSet::getSensorStatus(const std::string& deviceId) {
    auto it = sensors_.find(deviceId);

    if(it == sensors_.end()) {
        return TempHumidSensorStatus();
    }

    return it->second.readSensorData();
}

std::vector<DeviceData> SerialDirectDeviceInstanceSet::acquisitionTempHumidSensorData() {
    std::vector<DeviceData> sensorDataList;
    sensorDataList.reserve(sensors_.size());

    for(auto& [key, sensor] : sensors_) {
        TempHumidSensorStatus status = sensor.readSensorData();
        sensorDataList.push_back(DeviceData (1,status) );
    }
    return sensorDataList;
}