#pragma once
struct RecordFileInfo {
    std::string fileId;
    std::string cameraId;
    std::time_t startTime;
    std::time_t endTime;
    std::string localPath;
    std::uint64_t size = 0;
};

class IRecordOperator {
public:
    virtual ~IRecordOperator() = default;

    // 初始化录像能力（如设置海康NVR计划）
    virtual bool initializeRecordPlan() = 0;
    
    // 查询录像文件/时间段
    virtual std::vector<RecordFileInfo> queryRecords(
        std::time_t start,
        std::time_t end) = 0;

    // 下载录像到本地
    virtual bool fetchRecordToLocal(
        std::time_t start,
        std::time_t end,
        const std::string& saveDir) = 0;
};


class PullerFactory {
public:
    static std::unique_ptr<RecordFactory> create(const std::string& brand) {
        // if (info.type == "RTSP") {
        //     return std::make_unique<RtspPuller>(info);
        // } else if (info.type == "HIK") {
        //     return std::make_unique<HikvisionPuller>(info);
        // }

        return nullptr;
    }
};