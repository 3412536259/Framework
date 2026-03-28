#pragma once
#include "data_layer/ai/ai_dao.h"
#include "business_layer/buffer/frame.h"
#include "business_layer/detection/detection_object.h"
#include "data_layer/ai/storage_ai.h"
class IDetectionService{
public:
    virtual ~IDetectionService() = default;

    // 初始化检测服务，加载模型等
    virtual  bool initialize() = 0;

    // 对单帧进行检测
    // virtual void detectFrame() = 0;

    // 对视频缓冲区的多帧进行检测
    virtual void detectBufferedFrames() = 0;

     // 重新加载模型
    virtual bool reloadModel() = 0;

    //得到检测结果
    virtual void getDetectionResultsByFrame() = 0;
};


class DetectionService : public IDetectionService{
public:    
    DetectionService(IModelDao& dao);
    
    ~DetectionService();

    bool initialize() override;

    void detectFrame(std::string& frame);

    void detectBufferedFrames() override;

    bool reloadModel() override;

    void getDetectionResultsByFrame() override;
    
private:
    void detectionLoop();  // 循环检测函数

    bool shouldDetect(const CameraFrameSnapshot& snapshot);

    bool preprocessFrame(const CameraFrameSnapshot& snapshot, image_buffer_t& image);

    void handleDetectResult(const CameraFrameSnapshot& snapshot,const object_detect_result_list& results);

    void releaseImageBuffer(image_buffer_t& img);//释放帧

private:
    IModelDao& modelDao; //，path，并且检测
    StorageResult storageDao;
    std::string modelPath  = "lib/modul/yolov8n_3588_i8.rknn";
    // FrameBuffer m_frameBuffer;//缓冲对象，从这里面去拿取视频帧
    //从配置文件里面去拿  得到模型，目标集   
    std::atomic<bool> m_running;    // 检测线程运行标记
    std::thread m_detectionThread;  // 后台检测线程
    std::shared_ptr<FrameBuffer> frameBuffer_;

    size_t roundRobinIndex_ = 0;
    
    // 每路摄像头上次检测时间
    std::mutex stateMutex_;
    std::unordered_map<std::string, uint64_t> lastDetectTimeMap_;

    std::unordered_map<std::string, uint64_t> lastProcessedFrameTsMap_;

    // 每路摄像头最新检测结果（提供给外部）
    std::unordered_map<std::string, DetectionResult> latestResults_;
};

