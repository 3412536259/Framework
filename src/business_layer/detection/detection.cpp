#include "business_layer/detection/detection.h"
#include "common/image_processor/image_processor.h"
#include "data_layer/stream_nvr/stream_nvr_object.h"
DetectionService::DetectionService(IModelDao& dao):modelDao(dao){

}

DetectionService::~DetectionService(){
    m_running = false;
    modelDao.release();

}

bool DetectionService::initialize() {
    if(!modelDao.initialize(modelPath)){
        return false;
    }
    return true;
}

void DetectionService::detectFrame(std::string& frame) {//测试
    if(frame.empty()) return ;

    image_buffer_t image;
    int ret = read_image(frame.c_str(),&image);
    if(ret < 0){
        std::cout << "DetectionService::detectFrame1" << std::endl;
        return;
    }
    std::cout << "DetectionService::detectFrame2" << std::endl;
    object_detect_result_list od_results;
    

    if(!modelDao.infer(&image,&od_results)){
        std::cout << "DetectionService::detectFrame3" << std::endl;
        return ;
    }
    std::cout << "DetectionService::detectFrame4" << std::endl;
    bool hasObject = od_results.count > 0;

    ImageProcessor::drawDetections(&image, od_results);
    std::cout << "DetectionService::detectFrame5" << std::endl;
    std::vector<unsigned char> outJpeg;

    ImageProcessor::compressToJpeg(&image,outJpeg);
    std::cout << "DetectionService::detectFrame6" << std::endl;
    ImageProcessor::saveJpegToFile(outJpeg,"/home/ztl/workspace/Framework/image");
    std::cout << "DetectionService::detectFrame7" << std::endl;
}

void DetectionService::detectBufferedFrames() {
    if (m_running) {
        return; // 已经在跑了
    }

    m_running = true;

    m_detectionThread = std::thread(&DetectionService::detectionLoop, this);
}

bool DetectionService::reloadModel() {
    // 停止线程
    m_running = false;

    if (m_detectionThread.joinable()) {
        m_detectionThread.join();
    }

    // 释放旧模型
    modelDao.release();

    // 重新初始化
    return modelDao.initialize(modelPath);
}

void DetectionService::getDetectionResultsByFrame() {

}

void DetectionService::detectionLoop() {
    while (m_running) {
        //这里有个是确认buffer里面是否真的存在帧
        //1.获取所有摄像头的帧

        auto frameInfos = frameBuffer_->getAllLastFrames();

        if(frameInfos.size()){
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

         // 2. 从中选择一个“本轮要检测”的摄像头
        CameraFrameSnapshot* selected = nullptr;
        size_t size = frameInfos.size();

        for (size_t i = 0; i < size; ++i) {
            size_t index = (roundRobinIndex_ + i) % size;

            if (shouldDetect(frameInfos[index])) {
                selected = &frameInfos[index];
                roundRobinIndex_ = (index + 1) % size;
                break;
            }
        }

        // 3. 如果这一轮没有任何可检测帧，就休眠
        if (!selected) {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            continue;
        }

        // 4. 预处理
        image_buffer_t image;
        memset(&image, 0, sizeof(image));

        if (!preprocessFrame(*selected, image)) {
            // std::cerr << "[DetectionService] preprocess failed, cameraId="<< selected->cameraInfo.cameraId << std::endl;
            releaseImageBuffer(image);
            continue;
        }

        // 5. 推理
        object_detect_result_list detectResults;
        memset(&detectResults, 0, sizeof(detectResults));

        bool inferOk = false;
        try {
            inferOk = modelDao.infer(&image, &detectResults);
        } catch (const std::exception& e) {
            std::cerr << "[DetectionService] infer exception: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "[DetectionService] infer unknown exception" << std::endl;
        }

        releaseImageBuffer(image);

        if (!inferOk) {
            // std::cerr << "[DetectionService] infer failed, cameraId="<< selected->cameraInfo.cameraId << std::endl;
            continue;
        }

         // 6. 保存状态 / 输出结果
        handleDetectResult(*selected, detectResults);


        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }  
//    日志
}

bool DetectionService::shouldDetect(const CameraFrameSnapshot& snapshot) {
    const auto& cam = snapshot.cameraInfo;
    const auto& frame = snapshot.frame;

    if (!frame || !frame->valid || !frame->frame) {
        return false;
    }

    if (cam.status != CameraStatus::ONLINE) {
        return false;
    }

    uint64_t nowMs = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count()
    );

    std::lock_guard<std::mutex> lock(stateMutex_);

    auto it = lastDetectTimeMap_.find(cam.cameraId);
    if (it != lastDetectTimeMap_.end()) {
        uint64_t diff = nowMs - it->second;

        // 例如每路摄像头最短 500ms 检测一次
        if (diff < 500) {
            return false;
        }
    }

    return true;
}


bool DetectionService::preprocessFrame(const CameraFrameSnapshot& snapshot, image_buffer_t& image){
    
    return false;
}

void DetectionService::handleDetectResult(const CameraFrameSnapshot& snapshot,const object_detect_result_list& results) {
    std::lock_guard<std::mutex> lock(stateMutex_);

    uint64_t nowMs = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count()
    );

    lastDetectTimeMap_[snapshot.cameraInfo.cameraId] = nowMs;
    lastProcessedFrameTsMap_[snapshot.cameraInfo.cameraId] = snapshot.timestamp;


    DetectionResult result;

    storageDao.updateResult(result);
    
}



// void DetectionService::handleDetectResult(const CameraFrameSnapshot& snapshot, const object_detect_result_list& results) {
//     DetectionResult finalResult;
//     finalResult.cameraInfo = snapshot.cameraInfo;
//     finalResult.frameTimestamp = snapshot.timestamp;

//     finalResult.detectTimestamp = static_cast<uint64_t>(
//         std::chrono::duration_cast<std::chrono::milliseconds>(
//             std::chrono::system_clock::now().time_since_epoch()
//         ).count()
//     );

//     for (int i = 0; i < results.count; ++i) {
//         const auto& obj = results.results[i];

//         DetectionBox box;
//         box.classId = obj.cls_id;
//         box.score = obj.prop;
//         box.left = obj.box.left;
//         box.top = obj.box.top;
//         box.right = obj.box.right;
//         box.bottom = obj.box.bottom;

//         if (obj.cls_id == 0) {
//             box.className = "person";
//             if (obj.prop > 0.5f) {
//                 finalResult.hasPerson = true;
//             }
//         } else if (obj.cls_id == 1) {
//             box.className = "helmet";
//             if (obj.prop > 0.5f) {
//                 finalResult.hasHelmet = true;
//             }
//         } else {
//             box.className = "unknown";
//         }

//         finalResult.boxes.push_back(box);
//     }

//     // 业务规则
//     if (finalResult.hasPerson && !finalResult.hasHelmet) {
//         finalResult.alarm = true;
//     }

//     {
//         std::lock_guard<std::mutex> lock(stateMutex_);

//         lastDetectTimeMap_[snapshot.cameraInfo.cameraId] = finalResult.detectTimestamp;
//         lastProcessedFrameTsMap_[snapshot.cameraInfo.cameraId] = snapshot.timestamp;
//         latestResults_[snapshot.cameraInfo.cameraId] = finalResult;
//     }
// }



void DetectionService::releaseImageBuffer(image_buffer_t& img) {
    if (img.virt_addr) {
        free(img.virt_addr);
        img.virt_addr = nullptr;
    }
}

