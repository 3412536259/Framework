#pragma once
#include "command_service.h"

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

	CommandStatus(Status status, const std::string& message = "")
		: status_(status), message_(message) {}
	Status getStatus() const { return status_; }
	std::string getMessage() const { return message_; }
private:
	Status status_;
	std::string message_;
};