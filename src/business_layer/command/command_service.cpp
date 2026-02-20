#include "command_service.h"
#include "business_layer/command/mqtt_service.h"
#include <memory>

CommandService::CommandService(ILobbyService& lobbyService)
	: _lobbyService(lobbyService)
{
	_mqttService = std::make_unique<MqttService>(*this);
	// 临时的 MQTT 连接参数，后续需要根据实际需求进行调整
	_mqttService->connect("localhost", 1883);
	_mqttService->subscribe("command/execute");
}

void CommandService::executeCommand(const Command& command)
{
	std::string cmdStr = command.getCommand();
	CommandStatus status(command, Status::InProgress, "Command is being processed");
	_commandQueue.addCommandStatus(status);
	// 临时的 MQTT 发布主题和消息格式，后续需要根据实际需求进行调整
	_mqttService->publish("command/status", status.getMessage());
}



void CommandService::reportCommandStatus()
{
	CommandStatus status = _commandQueue.getNext();
	if (status.getStatus() != Status::InProgress) {
		// 临时的 MQTT 发布主题和消息格式，后续需要根据实际需求进行调整
		_mqttService->publish("command/status", status.getMessage());
	}
}
