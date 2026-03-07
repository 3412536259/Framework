#pragma once
#include <iostream>
#include<thread>

class ILobbyService {
public:

	virtual void executeCommand(const Command& command) = 0;

	virtual ~ILobbyService() = default;
};

class MockLobbyService : public ILobbyService {
public:
	MockLobbyService() : m_commandService(this) {}

	void setMqttService(MqttService& mqttService) {
		//m_commandService.setMqttService(mqttService);
	}

	void executeCommand(const Command& command) {
		std::cout << "MockLobbyService executing command: " << command.getCommand() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));// 模拟命令执行的耗时
	}

	CommandService& getCommandService() {
		return m_commandService;
	}

private:
	void TimingProcessing(); //定时上传

	void TimingUpload();

	void TimingPullVideoFrame();

private:
	CommandService m_commandService; //命令
};