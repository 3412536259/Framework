#pragma once
#include <nlohmann/json.hpp>
#include "common/erro_code.h"
#include <optional>
using json = nlohmann::json;
template <typename T>
class LobbyResult{
public:
    bool success; // 操作是否成功
    ErrorCode::Code errorCode; // 错误码，成功时为 ErrorCode::Code::SUCCESS
    std::string message; // 相关信息的字符串
    std::optional<T> data; // 可选的数据字段，成功时包含返回数据，失败时为 std::nullopt


public:    
    static LobbyResult<T> Ok(const T& data){// 成功结果，包含数据
        return {true,ErrorCode::Code::SUCCESS,"success",data};
    } 

    static LobbyResult<T>Error(ErrorCode::Code code){//错误结果，包含错误码和对应的错误信息
        return {false,code,ErrorCode::getMessage(code),std::nullopt};
    } 
};

class DeviceStatusQuery{
public:
    explicit DeviceStatusQuery(const json& j){
        // 从JSON对象中提取查询参数并初始化成员变量
        // 例如：
       
    }

    static DeviceStatusQuery createMqttObject(const json& j);

    static DeviceStatusQuery createHttpObject(const json& j);

    bool isValid() const {
        // 实现查询参数的验证逻辑，例如检查必需的字段是否存在，值是否在合理范围内等
        return true; // 返回true表示查询有效，false表示无效
    } 


    



private:
    
};
class SensorQuery {

};
class EnvironmentQuery {

};
class FrameQuery {
public:
    explicit FrameQuery(const nlohmann::json& j){
        // 从JSON对象中提取查询参数并初始化成员变量
        // 例如：
        // cameraId = j.at("cameraId").get<std::string>();
        // timestamp = j.at("timestamp").get<std::string>();
    }


    bool isValid() const {
        // 实现查询参数的验证逻辑，例如检查必需的字段是否存在，值是否在合理范围内等
        return true; // 返回true表示查询有效，false表示无效
    } 
private:
    // std::string cameraId;
    // std::string timestamp;       
};
class HistoricalVideoQuery {
public:
    explicit HistoricalVideoQuery(const nlohmann::json& j){
        // 从JSON对象中提取查询参数并初始化成员变量
        // 例如：
        // cameraId = j.at("cameraId").get<std::string>();
        // timestamp = j.at("timestamp").get<std::string>();
    }


    bool isValid() const {
        // 实现查询参数的验证逻辑，例如检查必需的字段是否存在，值是否在合理范围内等
        return true; // 返回true表示查询有效，false表示无效
    } 
private:
    // std::string cameraId;
    // std::string timestamp; 
};
class AlarmQuery {
public:
    explicit AlarmQuery(const nlohmann::json& j){
        // 从JSON对象中提取查询参数并初始化成员变量
        // 例如：
        // cameraId = j.at("cameraId").get<std::string>();
        // timestamp = j.at("timestamp").get<std::string>();
    }


    bool isValid() const {
        // 实现查询参数的验证逻辑，例如检查必需的字段是否存在，值是否在合理范围内等
        return true; // 返回true表示查询有效，false表示无效
    } 
private:
    // std::string cameraId;
    // std::string timestamp; 
};
class DownloadHistoricalVideo {
public:
    explicit DownloadHistoricalVideo(const nlohmann::json& j){
        // 从JSON对象中提取查询参数并初始化成员变量
        // 例如：
        // cameraId = j.at("cameraId").get<std::string>();
        // timestamp = j.at("timestamp").get<std::string>();
    }


    bool isValid() const {
        // 实现查询参数的验证逻辑，例如检查必需的字段是否存在，值是否在合理范围内等
        return true; // 返回true表示查询有效，false表示无效
    } 
private:
    // std::string cameraId;
    // std::string timestamp; 
};
class DoorLockOperation {

};
class SolenoidValveOperation {
public:
    SolenoidValveOperation(const json& j);
    ~SolenoidValveOperation() = default;
    const std::string& getDeviceId() const;
    const std::string& getCmd() const;
private:
    std::string deviceId;
    std::string cmd;
    std::string sensorId;
    std::string cameraId;
    std::string nvrId;
    std::string reqSource;
};
class TrolleyOperation {

};
class CameraOperation {

};
class CameraConfiguration {

};
class BoxConfiguration {

};
class AIModelDeploy {

};
class AIModelEnable {

};
class AIModelDisable {

};
class AIModelUpdate {

};


#include <string>
#include <memory>
#include <chrono>

struct VideoFrame {
    // ===== 视频数据 =====
    // std::shared_ptr<cv::Mat> image;

    // ===== 元数据 =====
    std::string cameraId;
    std::string nvrId;

    std::chrono::system_clock::time_point timestamp;

    uint64_t frameIndex{0};
    bool isKeyFrame{false};

    // ===== 扩展空间 =====
    // 可扩展AI识别结果、报警标记等

    VideoFrame() = default;

    // VideoFrame(/*std::shared_ptr<cv::Mat> img,
    //            std::string camId,
    //            std::string nvr,
    //            uint64_t index,
    //            bool key*/)
    //     // : image(std::move(img)),
    //     //   cameraId(std::move(camId)),
    //     //   nvrId(std::move(nvr)),
    //     //   timestamp(std::chrono::system_clock::now()),
    //     //   frameIndex(index),
    //     //   isKeyFrame(key)
    // {}
};