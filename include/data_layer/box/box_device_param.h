#ifndef BOX_DEVICE_PARAM_H
#define BOX_DEVICE_PARAM_H

#include "box_config.h"
#include "camera_config.h"
#include "solenoid_config.h"
#include <vector>

class BoxDeviceParam {
    public:

        BoxDeviceParam() = default;
        ~BoxDeviceParam() = default;
    
    private:
        BoxConfig boxConfig;
        std::vector<SolenoidConfig> solenoidConfigs;
        std::vector<CameraConfig> cameraConfigs;
};

#endif