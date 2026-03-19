#ifndef PLC_SMOKE_DETECTOR_H
#define PLC_SMOKE_DETECTOR_H

#include "plc_device.h"
#include "plc_smoke_detector_status.h"
class PlcSmokeDetector : public PlcDevice {
    public:
        PlcSmokeDetector() = default;
        PlcSmokeDetector(const int& type,
                         const std::string& deviceId,
                         const std::string& name,
                         const std::string& bindSerialPort,
                         const std::string& slaveAddr,
                         const std::string& plcPort,
                         const std::string& regAddr);
        ~PlcSmokeDetector() override = default;

        std::unique_ptr<DeviceStatus> getStatus() const override ;

        PlcSmokeDetectorStatus queryStatus(int serialPortStatus);
    private:
        std::array<uint8_t,8> buildQueryCommand();
        void splitRegAddress(uint8_t& high,uint8_t& low);
        uint16_t buildCalcCRC(const uint8_t* data,size_t length);
        bool sendData(std::array<uint8_t,8> command,int serialPortStatus);
        int receviceData(unsigned char* recvBuf,int bufSize,int waotTime, int serialPortStatus);
        std::string plcPort_;
        std::string regAddr_;
        
};

#endif