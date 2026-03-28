#include "data_layer/ai/storage_ai.h"


void StorageResult::updateResult(const DetectionResult& result) {
    if (result.cameraInfo.cameraId.empty()) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    results_[result.cameraInfo.cameraId] = result;
}

std::optional<DetectionResult> StorageResult::getResult(const std::string& cameraId) const {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = results_.find(cameraId);
    if (it == results_.end()) {
        return std::nullopt;
    }

    return it->second;
}

std::vector<DetectionResult> StorageResult::getAllResults() const {
    std::lock_guard<std::mutex> lock(mutex_);

    std::vector<DetectionResult> all;
    all.reserve(results_.size());

    for (const auto& kv : results_) {
        all.push_back(kv.second);
    }

    return all;
}

void StorageResult::removeResult(const std::string& cameraId) {
    std::lock_guard<std::mutex> lock(mutex_);
    results_.erase(cameraId);
}

void StorageResult::clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    results_.clear();
}

bool StorageResult::hasResult(const std::string& cameraId) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return results_.find(cameraId) != results_.end();
}