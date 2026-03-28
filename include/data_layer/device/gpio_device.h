#ifndef GPIO_DEVICE_H
#define GPIO_DEVICE_H

#include "data_layer/device/device.h"
class GPIODevice : public Device {

    protected:
        GPIODevice(int type,
                   const std::string& deviceId,
                   const std::string& name,
                   int pin,
                   const std::string& direction)
                : Device(type,deviceId,name), 
                  pin_(pin),  
                  direction_(direction) {}
    public:
        virtual ~GPIODevice() = default;    

        int getPin() { return pin_; }
        std::string getDirection() { return direction_; }
    
    private:
        int pin_;
        std::string direction_;
};

#endif