#pragma once
#include <string>

// Command 封装了从 MQTT 接收的命令字符串

class Command {
public:
	Command() = default;

	Command(const std::string& cmd)
		: _cmd(cmd){}
	
	std::string getCommand() const { return _cmd; }

private:
	std::string _cmd;

	// 拆分未来可能的命令参数，暂时不实现
	void phaseCommand() {}
};