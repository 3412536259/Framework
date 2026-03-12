#include <csignal>
#include "business_layer/lobby/lobby_service.h"
#include "presentation_layer/http_service.h"
#include "business_layer/command/mqtt_command.h"
#include "business_layer/command/mqtt/mqtt_service.h"
#include "business_layer/command/command_service.h"
// 全局标志：控制程序是否继续运行
bool g_running = true;

// 信号处理函数：捕获Ctrl+C等退出信号，优雅退出
void signalHandler(int signum) {
     // 根据signum判断信号类型，输出更友好的日志
    if (signum == SIGINT) {
        std::cout << ">>> 接收到【Ctrl+C中断信号】(编号: " << signum << ")，正在优雅关闭系统..." << std::endl;
    } else if (signum == SIGTERM) {
        std::cout << ">>> 接收到【进程终止信号】(编号: " << signum << ")，正在优雅关闭系统..." << std::endl;
    } else {
        std::cout << ">>> 接收到未知信号(编号: " << signum << ")，正在优雅关闭系统..." << std::endl;
    }
    g_running = false;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    

    
    NetworkService* networkService = nullptr; // 先不绑定
    // DeviceService deviceService();
    
    SafetyService safetyService;
    
    CommandService commandService(networkService);

    Timer timer;
    LobbyService lobbyService(safetyService,commandService,timer);

    MQTTCommandController mqttController = MQTTCommandController(lobbyService);
    HTTPCommandController httpController = HTTPCommandController(lobbyService);

    MqttProtocol mqttProtocol;
    std::cout << " 1"<< std::endl;
    MqttService mqttService("192.168.1.150", 8085, mqttController , mqttProtocol);
    std::cout << " 2"<< std::endl;
    commandService.immitDependence(mqttService); // 这里是接口注入，不是 setter逻辑

    mqttService.start();
    std::cout << " 3"<< std::endl;
    // WebService webService("192.168.1.104", 8080, httpController);
    // webService.start();

    std::cout << std::endl;
    std::cout << ">>> 系统启动成功！服务已就绪 (进程(pid) ID: " << getpid() << ")" << std::endl; 
    
    std::cout << ">>> 按 Ctrl+C 停止服务" << std::endl;
    std::cout << "=============================================" << std::endl;


    while (g_running) {
        // 休眠100ms，减少CPU占用
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // 这里可以添加需要周期性执行的业务逻辑
        // 例如：lobbyService.doPeriodicTask();
    }


    std::cout << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << ">>> 开始关闭服务..." << std::endl;
    // webService.stop(); // 停止Web服务
    mqttService.stop(); // 停止MQTT服务
    std::cout << ">>> 服务已关闭，系统退出成功" << std::endl;
    std::cout << "=============================================" << std::endl;

    return 0;
}