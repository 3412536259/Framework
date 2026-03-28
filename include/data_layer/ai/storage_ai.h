#pragma once
#include "business_layer/detection/detection_object.h"
#include <optional>
#include <unordered_map>
#include <mutex>

//每次保存结果都保存在日志里面
class StorageResult {
public:
    StorageResult() = default;
    ~StorageResult() = default;

    // 保存 / 更新某一路摄像头结果
    void updateResult(const DetectionResult& result);

    // 根据 cameraId 获取某一路最新结果
    std::optional<DetectionResult> getResult(const std::string& cameraId) const;

    // 获取所有摄像头最新结果
    std::vector<DetectionResult> getAllResults() const;

    // 删除某一路摄像头结果
    void removeResult(const std::string& cameraId);

    // 清空所有结果
    void clear();

    // 是否存在某个 cameraId 的结果
    bool hasResult(const std::string& cameraId) const;

private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, DetectionResult> results_; //这里保存最新的，
};