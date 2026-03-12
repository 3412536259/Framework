#pragma once
#include <string>


enum class CommandState{

	STATE_IDLE,  //空闲
	STATE_PENDING,     // 待执行
    STATE_EXECUTING,   // 执行中
    STATE_SUCCESS,     // 执行成功
    STATE_FAILED,      // 执行失败
    STATE_TIMEOUT      // 执行超时
};

enum class CommandType
{
    TYPE_SOLENOID_OPEN,  // 打开电磁阀
    TYPE_SOLENOID_CLOSE, // 关闭电磁阀
    TYPE_CAMERA_HISTORY, // 查看摄像头历史视频
    TYPE_DEVICE_READ,    // 读取设备状态
    TYPE_DEVICE_CTRL,    // 控制设备（通用）
    TYPE_FRAME_EXTRACT,  // 实时提取帧（流媒体）
    TYPE_OTHER           // 其他业务命令
};


class Command {
public:
	Command(std::string id, CommandType type, std::string devId)
        : cmdId(std::move(id)), cmdType(type), deviceId(std::move(devId)),
          cmdState(CommandState::STATE_PENDING) {}

	~Command();
private:
	std::string cmdId;
	CommandType cmdType;
	CommandState cmdState;
	std::string deviceId;
	std::string cmdContent;
	long long createTime;
	long long executeTime;


};

class DeviceCommands{




};