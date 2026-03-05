#pragma once
#include <nlohmann/json.hpp>
class LobbyResult{
public:
    // NoPermission();


    // InvalidState();


    // FromCommandResult();


};

class DeviceStatusQuery{
public:
    explicit DeviceStatusQuery(const nlohmann::json& j){
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
#include <opencv2/opencv.hpp>

struct VideoFrame {
    // ===== 视频数据 =====
    std::shared_ptr<cv::Mat> image;

    // ===== 元数据 =====
    std::string cameraId;
    std::string nvrId;

    std::chrono::system_clock::time_point timestamp;

    uint64_t frameIndex{0};
    bool isKeyFrame{false};

    // ===== 扩展空间 =====
    // 可扩展AI识别结果、报警标记等

    VideoFrame() = default;

    VideoFrame(std::shared_ptr<cv::Mat> img,
               std::string camId,
               std::string nvr,
               uint64_t index,
               bool key)
        : image(std::move(img)),
          cameraId(std::move(camId)),
          nvrId(std::move(nvr)),
          timestamp(std::chrono::system_clock::now()),
          frameIndex(index),
          isKeyFrame(key)
    {}
};