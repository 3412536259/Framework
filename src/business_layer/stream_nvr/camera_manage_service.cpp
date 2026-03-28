
#include "business_layer/stream_nvr/camera_manage_service.h"
#include "common/log/log_manager.h"
#include "common/config/config_parser.h"
CameraManageService::CameraManageService(std::shared_ptr<FrameBuffer> buffer){
    buffer_ = buffer;
}


bool CameraManageService::initialize() {
    std::cout << "[CameraManageService] initialize start..." << std::endl;
    
     // 如果之前有 session，建议先停掉
    for (auto& [cameraId, session] : sessions) {
        if (session) {
            session->stop();
        }
    }
    sessions.clear();

    // 1. 初始化海康 SDK
    hikSdkManager_ = std::make_unique<HikvisionSdkManager>();
    if (!hikSdkManager_) {
        std::cerr << "[CameraManageService] create HikvisionSdkManager failed" << std::endl;
        return false;
    }

    if (!hikSdkManager_->initialize()) {
        std::cerr << "[CameraManageService] Hikvision SDK initialize failed" << std::endl;
        return false;
    }

    // 2. 从配置类获取系统配置
    NVRConfig config = ConfigParser::getInstance().getConfig().nvr;
    if(config.brand.size()){
        if(config.brand == "hikvision"){
            hikDeviceManager_ = std::make_shared<HikvisionLoginManager>();

            if (!hikDeviceManager_->login(config)) {
                std::cerr << "[CameraManageService] login NVR failed" << std::endl;
                return false;
            }
        }

        for (const auto& cameraInfo : ConfigParser::getInstance().getConfig().nvr_cameras) {

            CameraInfo camInfo = CameraInfo::createNVRCameraInfo(cameraInfo);
                
            auto session = std::make_shared<StreamSession>(camInfo,buffer_,config.brand,hikDeviceManager_);
            if (!session) {
                
                continue;
            }     
            sessions.emplace(camInfo.cameraId, session);
        }
    } else{
        auto camfig = ConfigParser::getInstance().getConfig().cameras;

       for (const auto& cameraInfo : camfig) {
            CameraInfo camInfo = CameraInfo::createCameraInfo(cameraInfo);
                
            auto session = std::make_shared<StreamSession>(camInfo,buffer_,"",nullptr);
            if (!session) {
                
                continue;
            }     
            sessions.emplace(camInfo.cameraId, session);
        } 
    }


    return true;
}
bool CameraManageService::startCamera(const std::string& cameraId) {
    
}

bool CameraManageService::stopCamera(const std::string& cameraId) {
    
}


bool CameraManageService::startAll() {
    

    return true;
}

bool CameraManageService::stopAll() {
    


    return true;
}


StreamSession* CameraManageService::getSession(const std::string& cameraId){
    
}

// bool CameraManageService::registerCamera(const CameraInfo& info) {
//     std::unique_ptr<IStreamPuller> puller;

//     if (info.vendor == CameraVendor::HIKVISION) {
//         puller = std::make_unique<HikvisionPuller>(info, *hikDeviceManager_);
//     }

//     auto session = std::make_shared<StreamSession>(info, std::move(puller));
//     sessions_[info.cameraId] = session;
//     return true;
// }