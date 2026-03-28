#include "data_layer/ai/ai_dao.h"


ModelDao::~ModelDao(){

}


bool ModelDao::initialize(const std::string& modelPath) {
    memset(&rknn_app_ctx_, 0, sizeof(rknn_app_context_t));

    if (init_post_process() != 0) {
        std::cerr << "init_post_process failed!" << std::endl;
        return false;
    }

    postprocess_inited_ = true;
    if(!initModel()){
        std::cerr<<"Failed to initialize YOLOV8 model!"<<std::endl;
        return false;
    }
    std::cout<<"Model loaded from "<<modelPath_<<std::endl;

    initialized_ = true;
    return true;    

};      

    
bool ModelDao::infer(image_buffer_t* rgb_image,object_detect_result_list* od_results) {
    if (!initialized_) return false;
    int ret = inference_yolov8_model(&rknn_app_ctx_, rgb_image, od_results);
    if(ret!=0){
        std::cerr<<"inference_yolov8_model failed! ret="<<ret<<std::endl;
        return false;
    }
    return true;
};

    
bool ModelDao::postProcess(/*原始输出*/ /*检测结果*/) {
    return true;
};

    
void ModelDao::release() {
    if (initialized_) {
        release_yolov8_model(&rknn_app_ctx_);
        initialized_ = false;
    }
    if (postprocess_inited_) {
        deinit_post_process();
        postprocess_inited_ = false;
    }

};

    
bool ModelDao::isInitialized() const {
    return initialized_;
};

bool ModelDao::initModel(){
    if (access(modelPath_.c_str(), F_OK) != 0) {
        std::cerr << "Error: RKNN model file not exist - " << modelPath_ << std::endl;
        return false;
    }
    // 前置检查2：文件是否可读
    if (access(modelPath_.c_str(), R_OK) != 0) {
        std::cerr << "Error: No read permission for RKNN file - " << modelPath_ << std::endl;
        return false;
    }


    int ret = init_yolov8_model(modelPath_.c_str(), &rknn_app_ctx_);
    if( ret != 0){
        std::cerr<<"Failed to initialize YOLOV8 model from "<<modelPath_<<std::endl;
        return false;
    }
    return true;
}