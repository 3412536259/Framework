#ifndef CAMERA_UTILS_H
#define CAMERA_UTILS_H

#include <libavutil/frame.h>

enum class Status {
    OFFLINE,
    ONLINE
};

struct FrameData {
    std::shared_ptr<AVFrame> frame;
    int64_t timestamp_ = 0;
}

#endif