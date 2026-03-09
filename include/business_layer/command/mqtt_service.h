#pragma once
#include "command.h"
#include "command_buffer.h"
#include <string>
#include <memory>

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

	// 给 MqttCallback 提供的接口：获取 CommandService 实例
	//CommandService& getCommandService() { return _commandService; }
private:
	//CommandService& _commandService;
	//CommandBuffer& _commandBuffer;
	std::unique_ptr<mqtt::async_client> _client;
	std::unique_ptr<class MqttCallback> _callback;
};
