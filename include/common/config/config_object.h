#pragma once
#include <string>
#include <vector>
#include <cstdint>

// ---------------- Nvr ----------------
struct NVRConfig {
    std::string nvrId;       
    std::string brand;       
    std::string ip;
    std::string username;
    std::string password;
    int port;        
};
// 摄像头配置（字段类型改为字符串）
struct NVRCameraConfig {
    std::string cameraId;   
    std::string nvrId;       
    std::string name;
    int channelNo;           // 通道号仍为 int（代码中分配）
    // std::string IPCIP;
    // int port;
    // std::string IPCUSER;
    // std::string IPCPWD;
};


// ---------------- Camera ----------------
struct CameraConfig {
    std::string id;
    std::string name;
    std::string url;
};

// ---------------- Serial ----------------
struct SerialConfigStruct {
    std::string port;
    int baudRate = 0;
    std::string parity;
    int stopBits = 1;
};

// ---------------- PLC 本体：直连配置 ----------------
struct PLCDirectConfig {
    SerialConfigStruct serial;
};

// ---------------- PLC 本体：网关配置 ----------------
struct PLCGatewayBase {
    std::string gatewayId;
    std::string gatewayIp;
    int gatewayPort = 0;
};

// ---------------- PLC 本体结构 ----------------
struct PLCConfig {
    std::string plcId;
    std::string name;
    uint8_t slaveId = 1;
    std::string connectionType; // direct / gateway

    bool hasSerial = false;
    PLCDirectConfig serialConfig;

    bool hasGateway = false;
    PLCGatewayBase gatewayConfig;
};


// ---------------- 下挂设备 ----------------
struct PLCDeviceConfig {
    std::string id;
    std::string plcId;   // 归属 PLC！！
    std::string name;
    std::string deviceType; // 设备类型，例如 "solenoid_valve"
    std::string registerAddress;   // "0x0001"
};


// ---------------- 温湿度Sensor ----------------
struct TempHumidSensorConfig {
    std::string id;
    std::string name;
    std::string type;
    SerialConfigStruct serial;
    
    std::string slaveAddr;
    std::string regAddr;
    int readRegs;
};


// ---------------- 门锁 ----------------
struct DoorLockConfig {
    std::string id;
    std::string name;
    int pin;
    std::string direction;
};

//---------------- 水浸传感器 ----------------
struct WaterLevelSensorConfig {
    std::string id;
    std::string name;
    int pin;
    std::string direction;
};


// ---------------- 烟感传感器 ----------------
struct SmokeDetectorConfig {
    std::string id;
    std::string name;
    int pin;
    std::string direction;
};


// ---------------- 红外传感器 ----------------
struct InfraredSensorConfig {
    std::string id;
    std::string name;
    int pin;
    std::string direction;
};


// ---------------- Gateway (业务网关信息) ----------------
struct GatewayConfig {
    std::string id;
    std::string name;
    std::string ip;
    std::string protocol;
    std::string status;
};

// ---------------- CarControl ----------------
struct CarControlConfig {
    std::string id;
    std::string name;
    SerialConfigStruct serial;
    // timing parameters (ms)
    int sendWindowMs = 600;       // total continuous send window
    int sendIntervalMs = 80;      // interval between sends
    int operateTimeoutMs = 1500;  // timeout for operate() waiting
};

// ---------------- Root ----------------
struct DeviceConfigRoot {
    std::string version;
    std::string description;
    std::string boxId = "1";

    NVRConfig nvr;
    std::vector<NVRCameraConfig> nvr_cameras;
    std::vector<CameraConfig> cameras;
    std::vector<PLCConfig> plcs;            // <-- 新增
    std::vector<PLCDeviceConfig> plcDevices;
    std::vector<TempHumidSensorConfig> sensors;
    std::vector<DoorLockConfig> doorLocks;
    std::vector<InfraredSensorConfig> infraredSensors;
    std::vector<SmokeDetectorConfig> smokeDetectors;
    std::vector<WaterLevelSensorConfig> waterLevelSensors;
};