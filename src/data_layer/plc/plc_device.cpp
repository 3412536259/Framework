#include "plc_device.h"

PlcDevice::PlcDevice(const int& type,
                     const std::string& deviceId,
                     const std::string& name,
                     const std::string& bindSerialPort,
                     const std::string& slaveAddr)
                     : SerialDevice(type,deviceId,name,bindSerialPort),
                       slaveAddr_(slaveAddr){

}

DeviceStatus PlcDevice::getStatus() const {
    return new DeviceStatus();
}

std::string PlcDevice::getSlaveAddr() const {
    return slaveAddr_;
}