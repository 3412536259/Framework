#include "business_layer/command/command_object.h"
#include <sstream>  



SolenoidValveOperation::SolenoidValveOperation(const json& j){
        deviceId  = j.value("deviceId", "");
        cmd       = j.value("cmd", "");
        sensorId  = j.value("sensorId", "");
        cameraId  = j.value("cameraId", "");
        nvrId     = j.value("nvrId", "");
        reqSource = j.value("reqSource", "");
}


const std::string& SolenoidValveOperation::getDeviceId() const{
    return deviceId;
}
const std::string& SolenoidValveOperation::getCmd() const{
    return cmd;
}



Command::Command(std::string id, CommandType type, std::string devId)
        : cmdId(std::move(id)), cmdType(type), deviceId(std::move(devId)),
          cmdState(CommandState::STATE_IDLE) {auto now = std::chrono::system_clock::now();
                                              createTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                                              executeTime = 0; // 执行时间默认为0
}

Command Command::createOperateSolenoid(const SolenoidValveOperation& solenoid) {

    // std::string cmdId = "CMD_SOLENOID_" + std::to_string(id);
    Command cmd("0", CommandType::TYPE_SOLENOID_OPEN, "DEVICE_DEFAULT");
    // cmd.cmdContent = solenoid.open ? "OPEN_SOLENOID" : "CLOSE_SOLENOID";
    return cmd;
}

Command Command::createHistoricalVideo(DownloadHistoricalVideo& download) {
    // std::string cmdId = "CMD_VIDEO_" + std::to_string(id);
    Command cmd(0, CommandType::TYPE_CAMERA_HISTORY, "DEVICE_DEFAULT");
    // cmd.cmdContent = "DOWNLOAD_VIDEO[" + download.startTime + "~" + download.endTime + "]";
    return cmd;
}

std::string Command::getCmdId() const { return cmdId; }
CommandType Command::getCmdType() const { return cmdType; }
CommandState Command::getCmdState() const { return cmdState; }
std::string Command::getDeviceId() const { return deviceId; }
std::string Command::getCmdContent() const { return cmdContent; }

long long Command::getCreateTime() const { return createTime; }
long long Command::getExecuteTime() const { return executeTime; }

void Command::setCmdState(CommandState state) {
    cmdState = state;
}

std::string Command::createCmdId(){
    static int id = 1;
    std::stringstream ss;
    ss << "CMD_" 
       << time(nullptr)    // 用时间戳保证唯一
       << "_" 
       << id++;
    return ss.str();
}