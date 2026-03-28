#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>
#include <unordered_map>
#include "data_layer/stream_nvr/stream_nvr_object.h"
class cameraInfo;
class CameraFrameSnapshot;
class FrameData;

class FrameBuffer {
public:
    // 显式构造函数，初始化队列容量
    explicit FrameBuffer(size_t cameraCapacity = 14) : cameraCapacity_(cameraCapacity) {}

    ~FrameBuffer();

    bool registerCamera(const CameraInfo& info);

    void updateFrame(const CameraInfo& info, std::shared_ptr<FrameData> frame);

    std::shared_ptr<FrameData> getLastFrame(const std::string& cameraId) const;

    bool getShapshout(const std::string& cameraId, CameraFrameSnapshot& out) const;

    std::vector<CameraFrameSnapshot> getAllLastFrames() const;

    void clearFrames();


private:
    size_t cameraCapacity_;                  // 队列最大容量
    mutable std::mutex mutex_;         // 互斥锁（mutable 允许 const 成员函数加锁）
    std::condition_variable cond_;      // 条件变量
    // key = cameraId
    std::unordered_map<std::string, CameraFrameSnapshot> frameMap;
};