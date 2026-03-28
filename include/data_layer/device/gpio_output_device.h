#ifndef GPIO_OUTPUT_DEVICE_H
#define GPIO_OUTPUT_DEVICE_H

#include "data_layer/device/gpio_device.h"
class GPIOOutputDevice : public GPIODevice {

    protected:
        GPIOOutputDevice(int type,
                         const std::string& deviceId,
                         const std::string& name,
                         int pin,
                         const std::string& direction)
                    : GPIODevice(type,deviceId,name,pin,direction) {}
    
    public:
        virtual ~GPIOOutputDevice() = default;
    
    private:
};

#endif