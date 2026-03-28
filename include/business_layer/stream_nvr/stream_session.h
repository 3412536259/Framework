#pragma once
#include "business_layer/buffer/frame.h"
#include "data_layer/stream_nvr/puller_stream.h"
#include "data_layer/stream_nvr/stream_nvr_object.h"
#include "data_layer/stream_nvr/storage_video.h"
#include <thread>
#include <atomic>
class StreamSession {
public:
    StreamSession(const CameraInfo& info,std::shared_ptr<FrameBuffer> buffer,const std::string brand,std::shared_ptr<NVRLoginManager> nvrLogin);

    ~StreamSession();

    bool start();
    bool stop();
    bool isRunning() const;
    bool initializeRecordPlan();

    std::vector<RecordFileInfo> queryRecords(std::time_t start, std::time_t end);
    bool downloadRecordsToLocal(std::time_t start, std::time_t end);
private:
    void pullLoop();

private:
    CameraInfo info_;
    std::shared_ptr<FrameBuffer> frameBuffer_;     
    std::unique_ptr<IStreamPuller> puller_;
    std::unique_ptr<IRecordOperator> recordOperator_;

    std::thread worker_;
    std::atomic<bool> running_;
};