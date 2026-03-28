#pragma once
#include <vector>
#include "business_layer/stream_nvr/stream_session.h"
#include "business_layer/stream_nvr/stream_object.h"
#include "data_layer/stream_nvr/hik_device_manager.h"
#include "data_layer/stream_nvr/sdk_init.h"
#include <unordered_map>
class ICameraManageService {
public:
    virtual ~ICameraManageService() = default;

    
    virtual bool initialize() = 0;

    virtual bool startCamera(const std::string& cameraId) = 0;
    virtual bool stopCamera(const std::string& cameraId) = 0;

    virtual bool startAll() = 0;
    virtual bool stopAll() = 0;

    virtual StreamSession* getSession(const std::string& cameraId) = 0;

};

class CameraManageService : public ICameraManageService {
public:
    CameraManageService(std::shared_ptr<FrameBuffer> buffer);
    ~CameraManageService() = default;

    bool initialize() override;
    bool startCamera(const std::string& cameraId) override;
    bool stopCamera(const std::string& cameraId) override;
    bool startAll() override;
    bool stopAll() override;

    StreamSession* getSession(const std::string& cameraId) override;

private:
    std::mutex mutex_;
    std::shared_ptr<FrameBuffer> buffer_;
    std::unordered_map<std::string, std::unique_ptr<StreamSession>> sessions;
    std::unique_ptr<ISdkRuntime> hikSdkManager_;

    std::shared_ptr<NVRLoginManager> hikDeviceManager_;
};