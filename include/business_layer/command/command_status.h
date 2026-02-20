#pragma once
#include "command.h"
#include <queue>

enum class Status {
	Success,
	Failure,
	InProgress,
	Timeout,
	InvalidCommand,
	Unauthorized,
	NotFound,
	InternalError
};

class CommandStatus {
public:

	CommandStatus(Command cmd, Status status, const std::string& message = "")
		: _command(cmd), _status(status), _message(message) {}
	Status getStatus() const { return _status; }
	std::string getMessage() const { return _message; }
private:
	Command _command;
	Status _status;
	std::string _message;
};

class CommandQueue {
public:
	void addCommandStatus(const CommandStatus& commandStatus) {
		_queue.push(commandStatus);
	}
	bool hasNext() const {
		return !_queue.empty();
	}
	CommandStatus getNext() {
		if (_queue.empty()) {
			return CommandStatus(Command("empty"), Status::NotFound, "No command status available");
		}
		CommandStatus next = _queue.front();
		_queue.pop();
		return next;
	}
private:
	std::queue<CommandStatus> _queue;
};