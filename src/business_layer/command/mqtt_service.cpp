#include "business_layer/command/mqtt_service.h"
#include "common/mqtt/include/mqtt/async_client.h"
#include "common/mqtt/include/mqtt/connect_options.h"
#include "common/mqtt/include/mqtt/message.h"
#include "common/mqtt/include/mqtt/callback.h"
#include "business_layer/command/command_service.h"
#include "business_layer/command/mqtt_service.h" 
#include <iostream>
#include <memory>
#include <ctime>

// 继承自 mqtt::callback 的回调类，必须实现的回调方法包括 message_arrived、connected、connection_lost 和 delivery_complete
class MqttCallback : public mqtt::callback {
private:
	MqttService& _mqttService;

public:
    MqttCallback(MqttService& mqttService) : _mqttService(mqttService){}
	~MqttCallback() = default;

    void message_arrived(mqtt::const_message_ptr msg) override {
		// 当接收到 MQTT 消息时，这个方法会被调用
        // TODO: 解析消息并创建 Command 对象
        // Command command = parseMessage(msg->get_payload_str());
        std::cout << "Message arrived: " << msg->get_topic() << " - " << msg->get_payload_str() << std::endl;
		Command command(msg->get_payload_str());
		_mqttService.getCommandService().executeCommand(command);
    }

    void connected(const std::string& /*cause*/) override{
		// 连接成功回调
		std::cerr << "MQTT connected" << std::endl;
    }

    void connection_lost(const std::string& cause) override {
		// 连接丢失回调
		std::cerr << "MQTT connection lost, auto reconnecting... " << cause << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {
        // 消息发送完成回调
    }

};

// 实现 MqttService 类的方法

MqttService::MqttService(CommandService& commandService)  : _commandService(commandService) {
    // 构造函数实现
}

MqttService::~MqttService() = default;

bool MqttService::connect(const std::string& brokerAddress, int port) {
    if (_client && _client->is_connected()) {
        std::cerr << "MQTT client already connected" << std::endl;
        return true;
	}

    try {
        std::string serverAddress = "tcp://" + brokerAddress + ":" + std::to_string(port);
        std::string clientId = "framework-client-" + std::to_string(std::time(nullptr));

        _callback = std::make_unique<MqttCallback>(*this);
        _client = std::make_unique<mqtt::async_client>(serverAddress, clientId);
        _client->set_callback(*_callback);

        mqtt::connect_options connOpts;
        connOpts.set_clean_session(true);
        // 启用自动重连，初始重试间隔为1秒，最大重试间隔为10秒
		connOpts.set_automatic_reconnect(1, 10); 

        std::cout << "Connecting to MQTT broker: " << serverAddress << std::endl;
        mqtt::token_ptr connToken = _client->connect(connOpts);
        // 等待连接完成,设置超时时间
        if (connToken->wait_for(std::chrono::seconds(5))) {
            std::cout << "Connected to MQTT broker" << std::endl;
            return true;
        }
    } catch (const mqtt::exception& exc) {
        std::cerr << "MQTT connection error: " << exc.what() << std::endl;
        return false;
	}
	return false;
}

void MqttService::disconnect() {
    if (_client && _client->is_connected()) {
        try {
            std::cout << "Disconnecting from MQTT broker" << std::endl;
            mqtt::token_ptr disconnToken = _client->disconnect();
			disconnToken->wait();// 等待断开连接完成
            std::cout << "Disconnected from MQTT broker" << std::endl;
        } catch (const mqtt::exception& exc) {
            std::cerr << "MQTT disconnection error: " << exc.what() << std::endl;
        }
    }
}

bool MqttService::publish(const std::string& topic, const std::string& message) {
    if (!_client || !_client->is_connected()) {
        std::cerr << "MQTT client not connected" << std::endl;
        return false;
    }

    try {
        mqtt::message_ptr pubMsg = mqtt::make_message(topic, message);
		// QoS 0：最多一次; QoS 1：至少一次; QoS 2：只有一次
        // publish(pubMsg)不可以设置->wait(),会造成死锁
        pubMsg->set_qos(1);
        _client->publish(pubMsg);
		std::cerr << "MQTT published message to topic: " << topic << " - " << message << std::endl;
        return true;
    } catch (const mqtt::exception& exc) {
        std::cerr << "MQTT publish error: " << exc.what() << std::endl;
        return false;
    }
}

bool MqttService::subscribe(const std::string& topic) {
    if (!_client || !_client->is_connected()) {
        std::cerr << "MQTT client not connected" << std::endl;
        return false;
    }

    try {
        _client->subscribe(topic, 1)->wait();
        std::cout << "Subscribed to topic: " << topic << std::endl;
        return true;
    } catch (const mqtt::exception& exc) {
        std::cerr << "MQTT subscribe error: " << exc.what() << std::endl;
        return false;
    }
}

bool MqttService::unsubscribe(const std::string& topic) {
    if (!_client || !_client->is_connected()) {
        std::cerr << "MQTT client not connected" << std::endl;
        return false;
    }

    try {
        _client->unsubscribe(topic)->wait();
        std::cout << "Unsubscribed from topic: " << topic << std::endl;
        return true;
    } catch (const mqtt::exception& exc) {
        std::cerr << "MQTT unsubscribe error: " << exc.what() << std::endl;
        return false;
    }
}