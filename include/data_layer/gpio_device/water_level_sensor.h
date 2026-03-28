#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#include "data_layer/device/gpio_input_device.h"
#include "data_layer/gpio_device/water_level_sensor_status.h"
class WaterLevelSensor : public GPIOInputDevice {
    public:
        WaterLevelSensor();
        WaterLevelSensor(int type,
                         const std::string& deviceId,
                         const std::string& name,
                         int pin,
                         const std::string& direction);
        ~WaterLevelSensor() override = default;

        std::unique_ptr<DeviceStatus> getStatus() const override ;

        WaterLevelSensorStatus queryStatus();
    
    private:
        bool isGPIOExport();
        void exitGPIO();
        bool exportGPIO();
        bool setGPIOInput();
        bool setWaterLevelSensorValue();
        std::string buildGPIONum();
        std::string buildGPIOPath();    
};

#endif