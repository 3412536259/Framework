#ifndef PHYSICAL_CAMERA_H
#define PHYSICAL_CAMERA_H

#include <cstdint>
#include <memory>
#include <cstddef>

struct FrameData {
    std::string cameraId;
    int64_t timestamp;
    int width;
    int height;
    PixelFormat format;
    std::shared_ptr<FrameBuffer> buffer;
};

class FrameBuffer {
    public:
        uint8_t* data;
        size_t size;

};

enum class PixelFormat {
    YUV420P,//FFmpeg默认
    NV12,//硬件解码
    RGB24,//显示用
    BGR24,
    UNKNOWN
};

#endif