#pragma once 
#include "task_service.h"

class ILobbyService {
public:
    // 查询
    virtual LobbyResult retrieveDeviceStatus(const DeviceStatusQuery& query) = 0;
    virtual LobbyResult retrieveLiveCameraFrame(const FrameQuery& query) = 0;
    virtual LobbyResult retrieveHistoricalCameraFootage(const HistoricalVideoQuery& query) = 0;

    // 下载
    virtual LobbyResult downloadHistoricalCameraFootage(const DownloadHistoricalVideo& download) = 0;

    // 控制
    virtual LobbyResult operateSolenoidValve(const SolenoidValveOperation& operation) = 0;

    virtual LobbyResult controlTrolleyRotation(const TrolleyOperation& operation) = 0;

    virtual LobbyResult controlRotateCamera(const CameraOperation& operation) = 0;

    virtual LobbyResult configureCamera(const CameraConfiguration& config) = 0;

    // 配置
    virtual LobbyResult updateBoxConfiguration(const BoxConfiguration& configuration) = 0;

    // AI 模型
    virtual LobbyResult deployAIModel(const AIModelDeploy& deploy) = 0;
    virtual LobbyResult enableAIModel(const AIModelEnable& enable) = 0;
    virtual LobbyResult disableAIModel(const AIModelDisable& disable) = 0;
    virtual LobbyResult updateAIModel(const AIModelUpdate& update) = 0;

    virtual ~ILobbyService() = default;
};



class LobbyService : public ILobbyService{
public:
    LobbyService(IDeviceService& deviceService, ISafetyService& safetyService, ICommandService& commandService, IDetectionService& detectionService);
    ~LobbyService() = default;  

    LobbyResult retrieveDeviceStatus(const DeviceStatusQuery& query) override;

    LobbyResult retrieveLiveCameraFrame(const FrameQuery& query) override;

    LobbyResult retrieveHistoricalCameraFootage(const HistoricalVideoQuery& query) override;

    // 下载
    LobbyResult downloadHistoricalCameraFootage(const DownloadHistoricalVideo& download) override;

    // 控制
    LobbyResult operateSolenoidValve(const SolenoidValveOperation& operation) override;
   
    LobbyResult controlTrolleyRotation(const TrolleyOperation& operation) override;

    LobbyResult controlRotateCamera(const CameraOperation& operation) override;

    LobbyResult configureCamera(const CameraConfiguration& config) override;

    // 配置
    LobbyResult updateBoxConfiguration(const BoxConfiguration& configuration) override;

    // AI 模型
    LobbyResult deployAIModel(const AIModelDeploy& deploy) override;
    LobbyResult enableAIModel(const AIModelEnable& enable) override;
    LobbyResult disableAIModel(const AIModelDisable& disable) override;
    LobbyResult updateAIModel(const AIModelUpdate& update) override;

private:
    void TimingProcessing(); //定时上传

    void TimingUpload();

    void TimingPullVideoFrame();




private:

    IDeviceService& m_deviceService; // 设备

    ISafetyService& m_safetykService; // 安全
     
    ICommandService& m_commandService; //命令

    IDetectionService& m_detectionService; // 检测





};