#include "common/config/config_parser.h"

#include <iostream>
#include <fstream>

using json = nlohmann::json;
ConfigParser& ConfigParser::getInstance() {
    static ConfigParser instance;
    return instance;
}

bool ConfigParser::loadFromFile(const std::string& path) {
    
    if(isLoaded_) return true;

    std::ifstream ifs(path);
    if(!ifs.is_open()) {
        //日志输出
        return false;
    }

    json j;
    try {
        ifs >> j;
    } catch (std::exception& e) {
        std::cerr << "[ConfigParser] JSON parse error: " << e.what() << "\n";
        return false;
    }

    auto& root = j["device_config"];

    config_.boxId = root.value("box","");

    auto& devs = root["devices"];

    parseNVR(devs);
    parseNVRCameras(devs);
    parseCameras(devs);
    parsePLCList(devs);
    parsePLCDevices(devs);
    parseGPIODoorLocks(devs);
    parseGPIOInfraredSensors(devs);
    parseGPIOSmokeDetectors(devs);
    parseGPIOWaterLevelSensors(devs);
    parseTempHumidSensors(devs);
    isLoaded_ = true;
    return true;
}

void ConfigParser::parseNVR(const json& j)
{
    NVRConfig nvr;
    if (!j.contains("nvr")) {
        // throw std::runtime_error("devices节点下缺少nvr子节点");
    }
    const json& nvrJson = j["nvr"];
    // 解析string类型nvrId（直接读字符串）
    nvr.nvrId = nvrJson.value("nvrId", "");          
    nvr.brand = nvrJson.value("brand", "");         
    nvr.ip = nvrJson.value("ip", "");              
    nvr.username = nvrJson.value("username", "");   
    nvr.password = nvrJson.value("password", "");   
    // 解析int类型port（JSON自动转整型）
    nvr.port = nvrJson.value("port", 0);           

    // 校验：string nvrId判空，int port判0
    if (nvr.nvrId.empty()) { // 字符串ID判空
        throw std::runtime_error("NVR配置缺少有效nvrId（字符串）");
    }
    if (nvr.ip.empty()) {
        throw std::runtime_error("NVR配置缺少ip字段");
    }
    if (nvr.port == 0) { // 整型端口判0
        throw std::runtime_error("NVR配置缺少有效port（整型）");
    }
    config_.nvr = nvr;
}

void ConfigParser::parseNVRCameras(const json& j)
{
    config_.nvr_cameras.clear();
    if (!j.contains("camera")) {
        std::cerr << "[ConfigParser] devices节点下缺少camera子节点\n";
        return;
    }

    for (const auto& item : j["camera"]) {
        NVRCameraConfig camera;
        // 解析string类型ID（直接读字符串）
        camera.cameraId = item.value("id", "");  
        camera.nvrId = item.value("nvrId", "");        
        camera.name = item.value("name", ""); 
             
        camera.channelNo = 0; // 整型通道号初始化为0
        // 校验：string ID判空（不再判0）
        if (camera.cameraId.empty()) { // 字符串ID判空
            std::cerr << "[ConfigParser] 摄像头[" << camera.cameraId <<"]\n";
            std::cerr << "[ConfigParser] 摄像头配置缺少有效cameraId（字符串），跳过\n";
            continue;
        }
        if (camera.nvrId.empty()) { // 字符串ID判空
            std::cerr << "[ConfigParser] 摄像头[" << camera.cameraId << "]缺少有效nvrId（字符串），跳过\n";
            continue;
        }
        config_.nvr_cameras.push_back(camera);
        // camera.IPCIP  = item.value("IPCIP","");
        // camera.port = item.value("port",0);
        // camera.IPCUSER  = item.value("IPCUSER","");
        // camera.IPCPWD  = item.value("IPCPWD","");

    }
    // 关键：解析完摄像头后立即分配通道号
    if (!config_.nvr_cameras.empty()) {
        CameraChangeChannelNo(config_.nvr_cameras);
    } else {
        std::cerr << "[ConfigParser] 无有效摄像头配置，跳过通道号分配\n";
    }
}


void ConfigParser::parseCameras(const nlohmann::json& j) {
    if(!j.contains("camera")) return ;

    for(auto& item : j["camera"]) {
        CameraConfig c;
        c.id = item.value("id","");
        c.name = item.value("name","");
        c.url = item.value("url","");
        config_.cameras.push_back(c);
    }
}

void ConfigParser::parsePLCList(const nlohmann::json& j) {

} 
void ConfigParser::parsePLCDevices(const nlohmann::json& j) {

}

void ConfigParser::parseGPIODoorLocks(const nlohmann::json& j) {
    if(!j.contains("gpio_devices")) return;
    auto&  gpioDevices = j["gpio_devices"];
    if(!gpioDevices.contains("door_locks")) return ;
    for(auto& item : gpioDevices["door_locks"]) {
        DoorLockConfig d;
        d.id = item.value("id","");
        d.name = item.value("name","");
        d.pin = item.value("pin",0);
        d.direction = item.value("direction","");
        config_.doorLocks.push_back(d);
    }
}

void ConfigParser::parseGPIOInfraredSensors(const nlohmann::json& j) {
    if(!j.contains("gpio_devices")) return;
    auto&  gpioDevices = j["gpio_devices"];
    if(!gpioDevices.contains("infrared_sensors")) return ;
    for(auto& item : gpioDevices["infrared_sensors"]) {
        InfraredSensorConfig d;
        d.id = item.value("id","");
        d.name = item.value("name","");
        d.pin = item.value("pin",0);
        d.direction = item.value("direction","");
        config_.infraredSensors.push_back(d);
    }
}

void ConfigParser::parseGPIOSmokeDetectors(const nlohmann::json& j) {
    if(!j.contains("gpio_devices")) return;
    auto&  gpioDevices = j["gpio_devices"];
    if(!gpioDevices.contains("smoke_detectors")) return ;
    for(auto& item : gpioDevices["smoke_detectors"]) {
        SmokeDetectorConfig d;
        d.id = item.value("id","");
        d.name = item.value("name","");
        d.pin = item.value("pin",0);
        d.direction = item.value("direction","");
        config_.smokeDetectors.push_back(d);
    }
}

void ConfigParser::parseGPIOWaterLevelSensors(const nlohmann::json& j) {
    if(!j.contains("gpio_devices")) return;
    auto&  gpioDevices = j["gpio_devices"];
    if(!gpioDevices.contains("door_locks")) return ;
    for(auto& item : gpioDevices["water_level_sensors"]) {
        WaterLevelSensorConfig d;
        d.id = item.value("id","");
        d.name = item.value("name","");
        d.pin = item.value("pin",0);
        d.direction = item.value("direction","");
        config_.waterLevelSensors.push_back(d);
    }
}

void ConfigParser::parseTempHumidSensors(const nlohmann::json& j) {
    if(!j.contains("serial_direct_devices")) return;

    auto& devs = j["serial_direct_devices"];
    if(!devs.contains("temp_humid_sensor")) return;
    auto& tempHumid = devs["temp_humid_sensor"];

    auto& serialConfig = tempHumid["serial_config"];

    for(auto& item : tempHumid["sensors"]) {
        TempHumidSensorConfig config;

        config.id = item.value("id","");
        config.name = item.value("name","");
        config.slaveAddr = item.value("slave_addr","");
        config.regAddr = item.value("reg_addr","");
        config.readRegs = item.value("read_regs",2); 
        config.serial.port = serialConfig.value("port","");
        config.serial.baudRate = serialConfig.value("baud_rate",9600);
        config.serial.stopBits = serialConfig.value("stop_bits",1);
        config.serial.parity = serialConfig.value("parity","");
        config_.sensors.push_back(config);
    }

}

void  ConfigParser::CameraChangeChannelNo(std::vector<NVRCameraConfig>& cameras){
    if (cameras.empty()) {
        std::cerr << "[ConfigParser] 摄像头列表为空，无需分配通道号\n";
        return;
    }

    // 步骤1：按cameraId数值升序排序
    std::sort(cameras.begin(), cameras.end(), [this](const NVRCameraConfig& a, const NVRCameraConfig& b) {
        int idA = this->cameraIdToInt(a.cameraId);
        int idB = this->cameraIdToInt(b.cameraId);
        return idA < idB; // 升序排列
    });

    // 步骤2：从33开始分配通道号（修正原代码初始值32的笔误）
    int channelNo = 33; 
    for (auto& camera : cameras) {
        camera.channelNo = channelNo++;
        std::cout << "[ConfigParser] 摄像头[ID:" << camera.cameraId << "] 分配通道号: " << camera.channelNo << "\n";
    }
}

int  ConfigParser::cameraIdToInt(const std::string& cameraId){
    // 检查是否为纯数字
    for (char c : cameraId) {
        if (!isdigit(c)) {
            std::cerr << "[ConfigParser] 摄像头ID[" << cameraId << "]非纯数字，排到最后\n";
            return INT_MAX; // 非数字ID返回极大值
        }
    }
    return atoi(cameraId.c_str()); // 数字ID转为整数
}