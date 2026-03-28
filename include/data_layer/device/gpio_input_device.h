#ifndef GPIO_INPUT_DEVICE_H
#define GPIO_INPUT_DEVICE_H

#include "data_layer/device/gpio_device.h"
class GPIOInputDevice : public GPIODevice {

    protected:
        GPIOInputDevice(int type,
                        const std::string& deviceId,
                        const std::string& name,
                        int pin,
                        const std::string& direction)
                    : GPIODevice(type,deviceId,name,pin,direction) {}
    
    public:
        virtual ~GPIOInputDevice() = default;
    
    private:
};

#endif