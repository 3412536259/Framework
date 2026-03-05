#include <iostream>
#include "business_layer/lobby/lobby_service.h"
#include "presentation_layer/http_service.h"
int main(){

    
    // MqttService mqttService("0.0.0.0", 1883);

    // MqttCommandPublisher publisher(mqttService);

    // CommandService commandService(publisher);

    // 4️⃣ 构造其他服务（device / safety / detection）
    // DeviceService deviceService;
    // SafetyService safetyService;
    // DetectionService detectionService;

    // 5️⃣ 构造 LobbyService
    LobbyService lobbyService(/*deviceService,safetyService,commandService,detectionService*/);

    // 6️⃣ 构造 Controller
    // MTTPCommandController controller(lobbyService);

    // 7️⃣ 把 controller 注入 mqtt（回调）
    // mqttService.setController(controller);

    // mqttService.start();


    // HTTPCommandController controller = HTTPCommandController(lobbyService); 
    // WebService webService("0.0.0.0", 8080, controller); 

    // webService.start();

    // while (true) {} 
    
    
    return 0;
};