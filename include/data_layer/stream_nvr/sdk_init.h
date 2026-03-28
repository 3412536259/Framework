#pragma once
#include "lib/nvr/hikvision/HCNetSDK.h"
#include <mutex>
class ISdkRuntime {
public:
    virtual ~ISdkRuntime() = default;
    virtual bool initialize() = 0;
    virtual bool deinitSDK() = 0;
    virtual bool isInitialized() const = 0;
};

class HikvisionSdkManager : public ISdkRuntime {
public:
    HikvisionSdkManager() = default;
    ~HikvisionSdkManager() override;

    bool initialize() override;
    bool deinitSDK() override;
    bool isInitialized() const override;

private:
    mutable std::mutex mutex_;
    bool initialized_ = false;
};