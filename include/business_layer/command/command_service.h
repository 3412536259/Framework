#pragma once
#include "../lobby/lobby_service.h"
#include "command_status.h"

// command_status.h 定义了 CommandStatus 类，包含状态码和消息
// TODO: 调用 LobbyService 的方法来执行具体的命令，并根据结果返回 CommandStatus


class ICommandService {
public:
	virtual CommandResult executeCommand(const Command& command) = 0;
	virtual ~ICommandService() = default;
};

class CommandService : public ICommandService
{
public:
	CommandService(ILobbyService& lobbyService);
	~CommandService() = default;

	CommandStatus executeCommand(const Command& command) override;

private:
	ILobbyService& _lobbyService;
};


