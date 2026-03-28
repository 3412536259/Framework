#pragma once
#include <atomic>
#include <thread>
#include <unistd.h> 
#include <sys/stat.h>
#include <mutex>
#include <iostream>
extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
}
#include "common/yolo8/yolov8.h"
#include "image_utils.h"
//ai检测功能
class IModelDao{
public:
     virtual ~IModelDao() = default;

    
    virtual bool initialize(const std::string& modelPath) = 0;

    
    virtual bool infer(image_buffer_t* rgb_image,object_detect_result_list* od_results) = 0;

    
    virtual bool postProcess(/*原始输出*/ /*检测结果*/) = 0;

    
    virtual void release() = 0;

    
    virtual bool isInitialized() const = 0;
};

class ModelDao : public IModelDao{
public:
    ModelDao() = default;

    ~ModelDao();
    bool initialize(const std::string& modelPath) override;

    
    bool infer(image_buffer_t* rgb_image,object_detect_result_list* od_results) override;

    
    bool postProcess(/*原始输出*/ /*检测结果*/) override;

    
    void release() override;

    
    bool isInitialized() const override;

private:
   bool initModel();


private:

    
    std::string modelPath_;
    bool initialized_ = false;
    bool postprocess_inited_ = false;
    rknn_app_context_t rknn_app_ctx_;
    const int model_input_width_ = 640;
    const int model_input_height_ = 640;

};