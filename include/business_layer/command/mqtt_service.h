#pragma once
#include "command_service.h"

//TODO: 这个类的实现需要依赖一个 MQTT 客户端库，如 Paho MQTT C++，并且需要在构造函数中注入 ICommandService 来处理命令执行后的结果。

class MqttService {
public:
	MqttService(ICommandService& commandService);
	~MqttService() = default;
	bool connect(const std::string& brokerAddress, int port);
	void disconnect();
	bool publish(const std::string& topic, const std::string& message);
	bool subscribe(const std::string& topic);
	bool unsubscribe(const std::string& topic);
private:
	ICommandService& _commandService;
};
