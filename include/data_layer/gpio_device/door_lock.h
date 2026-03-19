#ifndef DOOR_LOCK_H
#define DOOR_LOCK_H

#include "gpio_output_device.h"
class DoorLock : public GPIOOutputDevice {

    public:
        DoorLock() = default;
        DoorLock(int type,
                 const std::string& deviceId,
                 const std::string& name,
                 int gpioGroup,
                 int gpioPinNum,
                 int pin,
                 const std::string& chipName,
                 const std::string& direction,
                 int initialValue,
                 const std::string& activeLogic);
        ~DoorLock() override = default;
    
        bool lockDoorLock();
        bool unlockDoorLock();

        std::unique_ptr<DeviceStatus> getStatus() const ;

        int queryDoorLockStatus();
    
    private:
        bool isGPIOExport();
        bool exportGPIO();
        bool setGPIODirection();
        std::string getGPIOSysPath() ;
};

#endif