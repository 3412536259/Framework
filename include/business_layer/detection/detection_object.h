#pragma once
#include <vector>
#include <string>
#include "data_layer/stream_nvr/stream_nvr_object.h"
struct DetectionBox {
    int classId = -1;
    std::string className;
    float score = 0.0f;

    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
};

struct DetectionResult {
    CameraInfo cameraInfo;
    uint64_t frameTimestamp = 0;
    uint64_t detectTimestamp = 0;

    bool valid = false;
    bool alarm = false;

    std::vector<DetectionBox> boxes;
};
