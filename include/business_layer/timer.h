#pragma once
#include "business_layer/buffer/equipment_status.h"
#include "business_layer/buffer/frame.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

class ITimer {
public:
    virtual void TimingProcessing() = 0; //定时更新函数

    virtual void TimingUpload() = 0; //定时上传函数

    virtual void TimingPullVideoFrame() = 0; //定时拉取视频帧函数

    virtual ~ITimer() = default;    
};

class Timer : public ITimer {
public:
    Timer() = default;
    ~Timer() = default;
    void TimingProcessing() override; //定时更新函数

    void TimingUpload() override; //定时上传函数

    void TimingPullVideoFrame() override; //定时拉取视频帧函数

private:
    // 定时器相关成员变量，如定时器ID、时间间隔等
    std::atomic<bool> m_running; // 定时器运行状态
    std::thread m_frame; // 帧定时器线程
    std::thread m_device_status; // 设备状态定时器线程
    std::atomic<int> g_frame_interval = 30;  // 帧周期（ms），可动态修改
    std::atomic<int> g_device_interval = 1000;// 设备周期（ms）

};
