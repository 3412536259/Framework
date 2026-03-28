#ifndef SMOKE_DETECTOR_H
#define SMOKE_DETECTOR_H

#include "data_layer/device/gpio_input_device.h"
#include "data_layer/gpio_device/smoke_detector_status.h"
class SmokeDetector : public  GPIOInputDevice{
    public:
        SmokeDetector() = default;
        SmokeDetector(int type,
                      const std::string& deviceId,
                      const std::string& name,
                      int pin,
                      const std::string& direction);
        ~SmokeDetector() override = default;

        std::unique_ptr<DeviceStatus> getStatus() const override ;

        SmokeDetectorStatus queryStatus();
    private:
        bool isGPIOExport();
        void exitGPIO();
        bool exportGPIO();
        bool setGPIOInput();
        std::string buildGPIONum();
        std::string buildGPIOPath();
        
};

#endif