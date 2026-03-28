#include "business_layer/detection/detection.h"
#include "common/config/config_parser.h"
#include  "business_layer/stream_nvr/stream_service.h"
#define DISABLE_RGA 1 
const std::string CONFIGPATH = "/home/ztl/workspace/Framework/include/common/config/config.json";

int main(){

    if(!ConfigParser::getInstance().loadFromFile(CONFIGPATH)) {
        std::cout << "配置文件加载失败" << std::endl;
    }

    // ModelDao dao;
    // DetectionService detectionService(dao);

    try {
        // 1. 创建共享帧缓冲区
        auto frameBuffer = std::make_shared<FrameBuffer>();

        // 2. 创建设备管理服务
        std::shared_ptr<ICameraManageService> cameraMgr =std::make_shared<CameraManageService>(frameBuffer);

        // 3. 创建流服务
        std::shared_ptr<IStreamService> streamService =std::make_shared<StreamService>(cameraMgr, frameBuffer);

        // 4. 初始化设备管理
        if (!cameraMgr->initialize()) {
            std::cerr << "[main] CameraManageService initialize failed!" << std::endl;
            return -1;
        }

        // // 5. 初始化流服务
        // if (!streamService->initialize()) {
        //     std::cerr << "[main] StreamService initialize failed!" << std::endl;
        //     return -1;
        // }

        // 6. 启动所有流
        if (!streamService->startStreamPull()) {
            std::cerr << "[main] StreamService startAll failed!" << std::endl;
            return -1;
        }

        std::cout << "[main] Stream system is running..." << std::endl;

        // 7. 主线程阻塞（简单版本）
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        // 8. 停止（一般不会走到这里）
        streamService->stopStreamPull();
        cameraMgr->stopAll();

    } catch (const std::exception& e) {
        std::cerr << "[main] Exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;

    
}