#include "command_service.h"  
#include "business_layer/command/mqtt_service.h"
#include "MockLobby.h"
#include <memory>
#include <iostream>

CommandService::CommandService(ILobbyService* lobbyService)
	: _lobbyService(lobbyService), _mqttService(nullptr)
{
	_lobbyService = dynamic_cast<MockLobbyService*>(_lobbyService);
}

void CommandService::setMqttService(MqttService& mqttService)
{
	_mqttService = &mqttService;
}

void CommandService::executeCommand(const Command& command)
{
	std::string cmdStr = command.getCommand();
	CommandStatus status(command, Status::InProgress, " Command is being processed ");
	_commandQueue.addCommandStatus(status);
	std::cout << "Executing command: " << cmdStr << std::endl;
	if (_mqttService) {
		_mqttService->publish("command/status", cmdStr + status.getMessage());
	}
	else {
		std::cerr << "MQTT service not set, cannot publish command status" << std::endl;
	}

	_lobbyService->executeCommand(command);
}



void CommandService::reportCommandStatus()
{
	CommandStatus status = _commandQueue.getNext();
	if (status.getStatus() != Status::InProgress) {
		if (_mqttService) {
			_mqttService->publish("command/status", status.getMessage());
		}
	}
}
