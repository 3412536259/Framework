#pragma once
//各种协议的流
#include <memory>
#include <vector>
#include <mutex>
#include <string>
#include <sstream> 
#include <iomanip>
#include <atomic>
#include <cstring> 
#include "data_layer/stream_nvr/stream_nvr_object.h"
#include "lib/nvr/hikvision/HCNetSDK.h"
extern "C" {
#include <libavutil/frame.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/time.h>
#include <libavutil/error.h>
#include <libavutil/avutil.h>
}
class IStreamPuller {
public:
    virtual ~IStreamPuller() = default;

    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual bool readFrame(FrameData& frame) = 0;
    
    virtual bool readFrameTime(FrameData& frame, int timeoutMs ) = 0;
    virtual std::shared_ptr<FrameData> getLatestFrame() = 0;
};




class RtspPuller : public IStreamPuller {

};

class HikvisionPuller : public IStreamPuller {
public:
    HikvisionPuller(const std::string userId, int channel);
    ~HikvisionPuller();
    bool open() override;//这个此时打开流
    void close() override;
    bool start() override;
    bool stop() override;
    bool readFrame(FrameData& frame) override;
    bool readFrameTime(FrameData& frame, int timeoutMs = 1000) override;
    std::shared_ptr<FrameData> getLatestFrame()override;
private:
    static void CALLBACK RealDataCallback(LONG lRealHandle,DWORD dwDataType,BYTE* pBuffer,DWORD dwBufSize,void* pUser);
    void handleRealData(DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize);
    bool initDecoder(); //这个只需要初始一次
    void onEncodedFrame(uint8_t* data, size_t len);
    AVCodecID detectCodec(uint8_t* data, size_t len);
private:
    int userId_ = -1;
    int realHandle_ = -1;
    int channel_;
    

    AVCodecContext* codecCtx_ = nullptr;
    AVFrame* frameYUV_ = nullptr;
    std::mutex decoderMutex_;
    bool decoderInitialized_ = false;

    FrameData lastKeyFrame_;

    // 状态
    std::atomic<bool> opened_{false};
    std::atomic<bool> started_{false};


    std::mutex mutex_;
    std::mutex frameMutex_;
    
};


class PullerFactory {
public:
    static std::unique_ptr<IStreamPuller> create(const std::string& brand) {
        // if (info.type == "RTSP") {
        //     return std::make_unique<RtspPuller>(info);
        // } else if (info.type == "HIK") {
        //     return std::make_unique<HikvisionPuller>(info);
        // }

        return nullptr;
    }
};