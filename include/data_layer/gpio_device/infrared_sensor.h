#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include "data_layer/device/gpio_input_device.h"
#include "data_layer/gpio_device/infrared_sensor_status.h"
class InfraredSensor : public GPIOInputDevice{

    public:
        InfraredSensor() = default;
        InfraredSensor(int type,
                       const std::string& deviceId,
                       const std::string& name,
                       int pin,
                       const std::string& direction);
        ~InfraredSensor() override = default;

        std::unique_ptr<DeviceStatus> getStatus() const override;

        InfraredSensorStatus queryStatus();
        

    private:
        bool isGPIOExport();
        void exitGPIO();
        bool exportGPIO();
        bool setGPIOInput();
        std::string buildGPIONum();
        std::string buildGPIOPath();

};

#endif