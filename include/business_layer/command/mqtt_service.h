#pragma once
#include "command.h"
#include <string>
#include <memory>

//TODO: 实现 MqttService 类，负责连接 MQTT 代理、订阅主题、接收消息并调用 CommandService 来执行命令。
// MqttService 还需要处理 MQTT 消息的解析和错误处理，并将命令执行结果通过 MQTT 发布到相应的主题上。

// 前向声明，避免循环依赖
class CommandService;
class MqttCallback;

namespace mqtt {
	class async_client;
	class delivery_token;
	typedef std::shared_ptr<delivery_token> delivery_token_ptr;
	class message;
	typedef std::shared_ptr<const message> const_message_ptr;
}

class MqttService {
public:
	MqttService(CommandService& commandService);
	~MqttService();
	bool connect(const std::string& brokerAddress, int port);
	void disconnect();
	bool publish(const std::string& topic, const std::string& message);
	bool subscribe(const std::string& topic);
	bool unsubscribe(const std::string& topic);
private:
	CommandService& _commandService;
	std::unique_ptr<mqtt::async_client> _client;
	std::unique_ptr<class MqttCallback> _callback;
};
