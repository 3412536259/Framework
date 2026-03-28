#pragma once
#include "business_layer/stream_nvr/camera_manage_service.h"
class IStreamService {
public:
    virtual ~IStreamService() = default;


    virtual bool startStreamPull() = 0;

    virtual bool stopStreamPull() = 0;

    // 上传时间表
    virtual bool queryRecordFiles(std::string cameraId,std::string startTime, std::string endTime,VideoFiles& outFiles) = 0;

    // 拉取录像到本地盒子
    virtual bool downloadRecordFile(DownloadVideoFile& in, DownloadReadyFile& out) = 0;

   
};

class StreamService : public IStreamService{
public:
    StreamService(std::shared_ptr<ICameraManageService> mgr,std::shared_ptr<FrameBuffer> buffer);

    ~StreamService() = default ;

    bool startStreamPull() override;

    bool stopStreamPull() override;

    bool queryRecordFiles(std::string cameraId,std::string startTime, std::string endTime,VideoFiles& outFiles) override;

    
    bool downloadRecordFile(DownloadVideoFile& in, DownloadReadyFile& out) override;
    
private:
    std::shared_ptr<ICameraManageService> manager_;




};