#include "mqtt_service.h"
#include "command_service.h"
//#include "lobby_service.h"
#include "MockLobby.h" // only for testing, not part of the actual implementation
#include "common/log/log.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>

//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h" // 基础文件输出的头文件

int main() {
	std::cout << "Starting MQTT Service Test..." << std::endl;
	Logger::getInstance().setLogPath("test.log");

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

    //// 1. 控制台日志（最简单用法）
    //spdlog::info("这是一条info级别的日志");
    //spdlog::warn("这是一条warn级别的日志，带参数：{}", 123);
    //spdlog::error("这是一条error级别的日志");

    //// 2. 文件日志（输出到文件，支持按大小/日期分割）
    //try {
    //    auto file_logger = spdlog::basic_logger_mt("file_logger", "app.log");
    //    file_logger->info("写入文件的日志");
    //    file_logger->set_level(spdlog::level::debug); // 设置日志级别
    //}
    //catch (const spdlog::spdlog_ex& ex) {
    //    spdlog::error("日志初始化失败: {}", ex.what());
    //}

    system("pause");

    return 0;
}

// 在Windows系统中使用Visual Studio 2022编译项目
// cd build
// cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug
// cmake --build . --config Debug

//  Mosquitto用于启动 Broker 和发布 MQTT 消息
// mosquitto -v
// mosquitto_pub -t "test/topic" -m "message for test/topic"
// sudo pkill -9 mosquitto