#include <csignal>
#include "business_layer/lobby/lobby_service.h"
#include "presentation_layer/http_service.h"
#include "business_layer/command/mqtt_command.h"
#include "business_layer/command/mqtt/mqtt_service.h"
#include "business_layer/command/command_service.h"
#include "common/log/log_manager.h"
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
    // 注册信号处理
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    std::cout << "=============================================" << std::endl;
    std::cout << "正在启动项目中....." << std::endl;

    // ====================== 设备任务初始化（原代码不变） ======================
    TempHumidSensorAcquisitionTask tempSensorTask = TempHumidSensorAcquisitionTask(1, 10);
    SerialDirectDeviceAcquisitionTask serialDeviceTask = SerialDirectDeviceAcquisitionTask(tempSensorTask); 

    SolenoidAcquisitionTask solenoidTask = SolenoidAcquisitionTask(0,10);           
    InfraredSensorAcquisitionTask infraredTask = InfraredSensorAcquisitionTask(4,10);
    WaterLevelSensorAcquisitionTask waterLevelTask = WaterLevelSensorAcquisitionTask(5,10);
    SmokeDetectorAcquisitionTask smokeTask = SmokeDetectorAcquisitionTask(6,10);

    PlcDeviceAcquisitionTask plcTask = PlcDeviceAcquisitionTask(solenoidTask,infraredTask,waterLevelTask,smokeTask);
    DoorLockAcquisitionTask doorLockTask = DoorLockAcquisitionTask(3,10);
    GPIODeviceAcquisitionTask gpioTask  = GPIODeviceAcquisitionTask(doorLockTask);

    DeviceAcquisitionTask deviceAcquisitionTask = DeviceAcquisitionTask(serialDeviceTask, plcTask,gpioTask);

    PlcDevice plcDevice = PlcDevice(10,"plc_001","111","?","0x01");
    std::vector<SolenoidValue> solenoidvalues ;
    SolenoidValue solenoid = SolenoidValue(0,"solenoid_001","001","00","00","00","00","00");
    solenoidvalues.push_back(solenoid);

    InfraredSensor infraredSensor = InfraredSensor(4,"11","11","211","1221","22","121");
    std::vector<InfraredSensor>  infraredSensors;
    infraredSensors.push_back(infraredSensor);

    std::vector<PlcSmokeDetector> smokeDetectors;
    PlcSmokeDetector smokeDetector = PlcSmokeDetector(5,"11","11","211","1221","22","121");
    smokeDetectors.push_back(smokeDetector);

    std::vector<PlcWaterLevelSensor> waterLevelSensors;
    PlcWaterLevelSensor waterSensor = PlcWaterLevelSensor(6,"11","11","211","1221","22","121");

    PlcInstance plcInsatnce = PlcInstance(plcDevice,SerialConfig(1,1,1,"11"),solenoidvalues,infraredSensors,smokeDetectors,waterLevelSensors);
    std::unordered_map<std::string, PlcInstance> plcMap;
    plcMap.emplace("plc_001",plcInsatnce);
    PlcInstanceSet plcInstances = PlcInstanceSet(plcMap);

    std::unordered_map<std::string,std::unique_ptr<Camera> >  cameras;
    cameras.emplace("camera_00x",std::make_unique<Camera> ("camera_00x","camera","") );
    CameraInstanceSet cameraInstances(std::move(cameras) );

    std::vector<DoorLock> doorLocks;
    doorLocks.reserve(5);
    doorLocks.push_back(DoorLock(3,"1","!",1,1,1,"1","1",1,"11"));
    GPIODeviceInstanceSet gpioInstanceSet = GPIODeviceInstanceSet(doorLocks);

    std::vector<TempHumidSensor> sensors;
    sensors.reserve(5);
    sensors.push_back(TempHumidSensor(1,"1","1","1","1","1",1,SerialConfig()));
    SerialDirectDeviceInstanceSet serialInstances = SerialDirectDeviceInstanceSet(sensors);

    DeviceManageService deviceManageService(std::move(plcInstances),std::move(cameraInstances),std::move(gpioInstanceSet),std::move(serialInstances));
    DeviceStatusCache deviceStatusCache = DeviceStatusCache();
    RealTimeFrameCache realTimeFrameCache = RealTimeFrameCache();

    DeviceService deviceService(deviceManageService,deviceStatusCache,deviceAcquisitionTask,realTimeFrameCache);

    // ====================== 日志系统初始化 + 失败处理 ======================
    auto queue = std::make_shared<BlockingQueue>();
    auto logger = std::make_shared<AsyncLogger>(queue);
    auto fileSink = std::make_shared<FileSink>("log");
    logger->addSink(fileSink);

    // 日志启动失败直接退出
    if (!logger->start()) {
        std::cerr << ">>> 错误：日志系统启动失败，程序退出" << std::endl;
        return -1;
    }
    LoggerManager::instance().registerLogger("work", logger);
    std::cout << ">>> 日志系统启动成功" << std::endl;

    // ====================== 数据库初始化 + 失败处理 ======================
    auto& dbManager = DatabaseManager::instance();
    if (!dbManager.init("/home/lin/Desktop/Framework/include/common/database")) {
        std::cerr << ">>> 错误：数据库初始化失败，程序退出" << std::endl;
        logger->stop();  // 清理已启动的日志
        return -1;
    }
    std::cout << ">>> 数据库初始化成功" << std::endl;

    CommandDao commandDao(dbManager.getCommandDB());
    NetworkService* networkService = nullptr;
    SafetyService safetyService;
    CommandService commandService(networkService, commandDao);
    Timer timer;
    LobbyService lobbyService(safetyService, commandService, deviceService, timer, deviceStatusCache);

    MQTTCommandController mqttController = MQTTCommandController(lobbyService);
    HTTPCommandController httpController = HTTPCommandController(lobbyService);

    MqttProtocol mqttProtocol;
    MqttService mqttService("192.168.1.104", 1883, mqttController, mqttProtocol);
    commandService.immitDependence(mqttService); 

    // ====================== MQTT 启动 + 失败处理（核心需求） ======================
    std::cout << ">>> 正在启动 MQTT 服务..." << std::endl;
    if (!mqttService.start()) {
        std::cerr << ">>> 错误：MQTT 服务启动失败，程序退出" << std::endl;
        // 只清理已经启动的资源，不调用 stop()
        logger->stop();
        return -1;
    }
    std::cout << ">>> MQTT 服务启动成功" << std::endl;

    // ====================== 所有服务启动完成 ======================
    std::cout << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << ">>> 系统启动成功！服务已就绪 (进程 ID: " << getpid() << ")" << std::endl; 
    std::cout << ">>> 按 Ctrl+C 停止服务" << std::endl;
    std::cout << "=============================================" << std::endl;

    // 主循环
    while (g_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // ====================== 优雅退出 ======================
    std::cout << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << ">>> 开始关闭服务..." << std::endl;
    
    mqttService.stop();
    logger->stop();
    
    std::cout << ">>> 服务已关闭，系统退出成功" << std::endl;
    std::cout << "=============================================" << std::endl;

    return 0;
}