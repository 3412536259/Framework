#pragma once
#include "command.h"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
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
	CommandStatus(Command cmd, Status status, const std::string& message = "");
	Status getStatus() const { return _status; }
	std::string getMessage() const { return _message; }

	void setStatus(Status status);

private:
	Command _command;
	Status _status;
	std::string _message;

	// 记录状态变化的日志
	void logStatusChange();
};

class CommandQueue {
public:
	CommandQueue();
	~CommandQueue();

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