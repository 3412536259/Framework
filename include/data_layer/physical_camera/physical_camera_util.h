#ifndef PHYSICAL_CAMERA_UTIL_H
#define PHYSICAL_CAMERA_UTIL_H

#include <cstdint>
#include <memory>
#include <cstddef>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavutil/pixfmt.h>
}

struct KeyFrame {
    std::string cameraId;
    std::shared_ptr<AVFrame> frame;
    int64_t timestamp;
};

//生成视频用
struct VideoPacket {
    AVPacket pkt;
    int64_t timestamp;
    bool isKeyFrame;
};



#endif