#pragma once

#include <string>
#include <mutex>
#include <climits> 
#include <cmath>
#include "common/config/json.hpp"
#include "common/config/config_object.h"


class ConfigParser {
    public:
        static ConfigParser& getInstance();

        bool loadFromFile(const std::string& path);
        const DeviceConfigRoot& getConfig() const { return config_; }
    
    private:
        ConfigParser() = default;
        ConfigParser(const ConfigParser&) = delete;
        ConfigParser& operator=(const ConfigParser&) = delete;

        void parseNVR(const nlohmann::json& j);  // j 直接是 device_config 下的 nvr 节点
        void parseNVRCameras(const nlohmann::json& j); // j 是 device_config.devices 节点
        void CameraChangeChannelNo(std::vector<NVRCameraConfig>& cameras);
        int cameraIdToInt(const std::string& cameraId);

        void parseCameras(const nlohmann::json& j);
        void parsePLCList(const nlohmann::json& j);
        void parsePLCDevices(const nlohmann::json& j);
        void parseGPIODoorLocks(const nlohmann::json& j);
        void parseGPIOInfraredSensors(const nlohmann::json& j);
        void parseGPIOSmokeDetectors(const nlohmann::json& j);
        void parseGPIOWaterLevelSensors(const nlohmann::json& j);
        void parseTempHumidSensors(const nlohmann::json& j);

        bool isLoaded_ = false;
        DeviceConfigRoot config_;
};

