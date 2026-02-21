#include "mqtt_service.h"
#include "command_service.h"
//#include "lobby_service.h"
#include "MockLobby.h" // only for testing, not part of the actual implementation
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>

int main() {
	MockLobbyService lobbyService;

    MqttService mqttService(lobbyService.getCommandService());

	lobbyService.setMqttService(mqttService);

    std::cout << "Connecting to MQTT broker..." << std::endl;
    if (mqttService.connect("localhost", 1883)) {
        std::cout << "Connected successfully!" << std::endl;
        
        mqttService.subscribe("test/topic");
        while(1){}
        /*mqttService.publish("test/topic", "Hello, MQTT!");
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        mqttService.disconnect();
        std::cout << "Disconnected." << std::endl;*/
    } else {
        std::cerr << "Failed to connect!" << std::endl;
    }

    system("pause");

    return 0;
}

// 编译命令示例（在 Windows 上使用 Visual Studio 2022）：
// cd build
// cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug
// cmake --build . --config Debug