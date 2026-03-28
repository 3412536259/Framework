#include "business_layer/stream_nvr/stream_service.h"

StreamService::StreamService(std::shared_ptr<ICameraManageService> mgr,std::shared_ptr<FrameBuffer> buffer)
        : manager_(mgr) {
        //    manager_->initialize(); //加载
        }

bool StreamService::startStreamPull() {
        return manager_->startAll();
    }

bool StreamService::stopStreamPull()  {
        return manager_->stopAll();
}
bool StreamService::queryRecordFiles(std::string cameraId,std::string startTime, std::string endTime,VideoFiles& outFiles){

}

bool StreamService:: downloadRecordFile(DownloadVideoFile& in, DownloadReadyFile& out){

}