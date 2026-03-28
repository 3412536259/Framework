#include "business_layer/stream/stream_service.h"

#include <iostream>
StreamService::StreamService() {
    startPullStream();
}

void StreamService::startPullStream() {
    std::cout << "111" << std::endl;
    if(running_) return;

    running_ = true;
    if(!registerDevices()) {
        //输出日志
        std::cout << "解析摄像头失败" <<std::endl;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    for(auto& camera : cameras_) {
        std::cout << "开始拉流!" <<std::endl;
        camera.second->startStreamPull();
    }


}

void StreamService::stopPullStream() {
    if(!running_) return;

    running_ = false;

    std::lock_guard<std::mutex> lock(mutex_);
    for(auto& camera : cameras_) {
        camera.second -> stopStreamPull();
    }
}

bool StreamService::registerDevices() {
    auto& config = ConfigParser::getInstance().getConfig();

    for(auto& camera : config.cameras) {
        auto c = std::make_shared<PhysicalCamera>(camera.id,camera.url,
                                          std::make_shared<PacketQueue>(16),
                                          std::make_unique<PacketDecoder>(),
                                          std::make_unique<StreamPuller>(camera.url));
        addCamera(c);
    }
    return true;
}

void StreamService::addCamera(std::shared_ptr<PhysicalCamera> camera) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::string id = camera -> getCameraId();
    if(cameras_.count(id)) return;

    cameras_.emplace(id,camera);
}