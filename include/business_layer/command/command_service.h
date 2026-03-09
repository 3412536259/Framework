#pragma once
#include "command_status.h"
#include <memory>
#include <queue>

// command_status.h 定义了 CommandStatus 类，包含状态码和消息
// TODO: 
// 1.调用 LobbyService 的方法来执行具体的命令，并根据结果返回 CommandStatus, 发布到 MQTT 主题上
// 2. 给大厅服务提供一个接口，让它能够上传盒子的状态

// 前向声明，避免循环依赖
class ILobbyService;
class MqttService;

class ICommandService {
public:
	virtual void executeCommand(const Command& command) = 0;
	virtual ~ICommandService() = default;
};

class CommandService : public ICommandService
{
public:
	CommandService(ILobbyService* lobbyService);
	~CommandService() = default;

	// 大厅服务调用这个方法来设置 MQTT 服务的引用，CommandService 将通过这个引用发布命令状态到 MQTT 主题上
	//void setMqttService(MqttService& mqttService);

	// 这个方法会被 MqttService 回调
	// 收到消息后发送 Command is being processed 到 MQTT 主题上，表示命令正在处理
	void executeCommand(const Command& command) override;

	// 大厅定时器定期触发这个方法，如果CommandStatus的状态不是 InProgress，将结果发布到 MQTT 主题上
	void reportCommandStatus();

	// 大厅服务调用这个方法来上传盒子的状态，CommandService 将状态发布到 MQTT 主题上
	//void uploadBoxStatus(const BoxStatus& status);

private:
	ILobbyService* _lobbyService = nullptr;
	MqttService* _mqttService = nullptr;
	CommandQueue _commandQueue;
};


