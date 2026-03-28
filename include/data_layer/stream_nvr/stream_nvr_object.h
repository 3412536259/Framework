#pragma once
#include <memory>
#include <string>
#include <cstdint> 
#include "common/config/config_object.h"
extern "C" {
#include <libavutil/frame.h>
}
class IStreamPuller;

// class DetectionResult{

// };



struct NVRInfo{
    std::string brank;
    std::string ip;
    std::string username;
    std::string password;
    short port;
};


struct FrameData {
    std::shared_ptr<AVFrame> frame;  // 解码后的 RGB/YUV
    int width = 0;
    int height = 0;
    // uint64_t timestamp = 0;
    bool valid = false;
    uint64_t lastKeyFrameTime ;
};

enum CameraStatus{ 
    ONLINE = 0,//在线
    RUNNING = 1,//运行
    OFFLINE = -1//离线
};
struct CameraInfo{//
    std::string  cameraId;
    std::string  nvrId;
    int channel;
    std::string name;
    CameraStatus status; 
    std::string ip;
    static CameraInfo createNVRCameraInfo(NVRCameraConfig);

    static CameraInfo createCameraInfo(CameraConfig);
};




struct CameraFrameSnapshot {
    CameraInfo cameraInfo;                    // 摄像头信息
    std::shared_ptr<FrameData> frame;         // 当前最新帧
    uint64_t timestamp = 0;                   // 更新时间
};


