#include "mqtt_service.h"
#include "command_service.h"
//#include "lobby_service.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>

class ILobbyService {
public:

    virtual ~ILobbyService() = default;
};

class MockLobbyService : public ILobbyService {
    public:
		MockLobbyService() : m_commandService(*this) {}

private:
    void TimingProcessing(); //定时上传

    void TimingUpload();

    void TimingPullVideoFrame();

private:
    CommandService m_commandService; //命令
};

int main() {
	MockLobbyService lobbyService;

	CommandService commandService(lobbyService);
    MqttService mqttService(commandService);

    std::cout << "Connecting to MQTT broker..." << std::endl;
    if (mqttService.connect("localhost", 1883)) {
        std::cout << "Connected successfully!" << std::endl;
        
        mqttService.subscribe("test/topic");
        mqttService.publish("test/topic", "Hello, MQTT!");
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        mqttService.disconnect();
        std::cout << "Disconnected." << std::endl;
    } else {
        std::cerr << "Failed to connect!" << std::endl;
    }

    system("pause");

    return 0;
}
