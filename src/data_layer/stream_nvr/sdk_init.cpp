#include "data_layer/stream_nvr/sdk_init.h"
#include "common/log/log_manager.h"

bool HikvisionSdkManager::initialize() {
    // 1. 初始化海康SDK
    if (!NET_DVR_Init()) {
        int err = NET_DVR_GetLastError();
        // 日志输出：错误码 + 描述（拼接字符串，保持信息完整）
        LOG_ERROR("[HikvisionSdkManager] SDK初始化失败，错误码：" + std::to_string(err));
        return false; 
    }

    // 2. 设置连接超时（2秒，1次重试）
    bool retConnect = NET_DVR_SetConnectTime(2000, 1);
    if (!retConnect) {
        int err = NET_DVR_GetLastError();
        LOG_WARNING("[HikvisionSdkManager] 设置连接超时失败，错误码：" + std::to_string(err));
    }

    // 3. 设置自动重连（10秒检测一次）
    bool retReconnect = NET_DVR_SetReconnect(10000, true);
    if (!retReconnect) {
        int err = NET_DVR_GetLastError();
        LOG_WARNING("[HikvisionSdkManager] 设置自动重连失败，错误码：" + std::to_string(err));
    }
    
    initialized_ = true;
    
    // 4. 初始化成功，记录日志 + 设置SDK原生日志
    LOG_INFO("[HikvisionSdkManager] SDK初始化成功，启用SDK原生日志");
    // NET_DVR_SetLogToFile(3, "./hik_sdk_log/", true);
    
    return true;
}

bool HikvisionSdkManager::deinitSDK() {
    // 1. 执行SDK清理
    if (!NET_DVR_Cleanup()) {
        int err = NET_DVR_GetLastError();
        // 替换std::cerr为LOG_ERROR，补充错误码
        LOG_ERROR("[HikvisionSdkManager] SDK反初始化失败，错误码：" + std::to_string(err));
        return false; // 清理失败，返回false
    }

    // 2. 清理成功，替换std::cout为LOG_INFO
    LOG_INFO("[HikvisionSdkManager] SDK反初始化成功");
    return true;
}   

bool HikvisionSdkManager::isInitialized() const {
    return this->initialized_;
}