#ifndef PLC_DEVICE_INFO_H
#define PLC_DEVICE_INFO_H
class SolenoidValveOperation;
#include <string>
class PlcDeviceInfo {
    public:
        PlcDeviceInfo() = default;
        PlcDeviceInfo(const std::string& plcId,
                      const std::string& deviceId);
        ~PlcDeviceInfo() = default;

        const std::string& getPlcId() const;
        const std::string& getDeviceId() const;
    
        static PlcDeviceInfo createPlcDevice(const SolenoidValveOperation& op);


    private:
        std::string plcId_;
        std::string deviceId_;
};

#endif