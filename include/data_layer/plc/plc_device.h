#ifndef PLC_DEVICE_H
#define PLC_DEVICE_H

#include <vector>
#include "serial_device.h"
class PlcDevice : public SerialDevice {

    public:
        PlcDevice(const int& type,
                  const std::string& deviceId,
                  const std::string& name,
                  const std::string& bindSerialPort,
                  const std::string& slaveAddr);
        ~PlcDevice() override = default;

        DeviceStatus getStatus() const override;

        std::string getSlaveAddr() const ;
    
    private:
        std::string slaveAddr_;
};

#endif