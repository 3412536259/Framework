#include "business_layer/buffer/frame.h"
#include "data_layer/stream_nvr/stream_nvr_object.h"

FrameBuffer::~FrameBuffer(){

}


bool FrameBuffer::registerCamera(const CameraInfo& info){
    std::lock_guard<std::mutex> lock(mutex_);

    if(cameraCapacity_ > 0 && frameMap.size() >= cameraCapacity_){

        return false;
    }

    if(frameMap.find(info.cameraId) != frameMap.end()){
        return true;
    }

    frameMap[info.cameraId] = CameraFrameSnapshot{info,nullptr,0};
    return true;
}

void FrameBuffer::updateFrame(const CameraInfo& info, std::shared_ptr<FrameData> frame){
    if(!frame) return ;

    std::lock_guard<std::mutex> lock(mutex_);

    auto it = frameMap.find(info.cameraId);
    if(it == frameMap.end()){
        //自动注册
        if(cameraCapacity_ > 0 && frameMap.size() >= cameraCapacity_){
            return ;
        }
        frameMap[info.cameraId] = CameraFrameSnapshot{info, std::move(frame), 0};
    }
    else {
        // 覆盖旧帧 + 更新摄像头信息
        // it->second.cameraInfo = info;
        it->second.frame = std::move(frame);
        it->second.timestamp = 0;
    } 
}

std::shared_ptr<FrameData> FrameBuffer::getLastFrame(const std::string& cameraId) const{
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = frameMap.find(cameraId);
    if (it == frameMap.end()) {
        return nullptr;
    }

    return it->second.frame;
}


bool FrameBuffer::getShapshout(const std::string& cameraId, CameraFrameSnapshot& out) const{
    std::lock_guard<std::mutex> lock(mutex_);

        auto it = frameMap.find(cameraId);
        if (it == frameMap.end()) {
            return false;
        }

        out = it->second;
        return true;
}

std::vector<CameraFrameSnapshot> FrameBuffer::getAllLastFrames() const{
    std::lock_guard<std::mutex> lock(mutex_);

    std::vector<CameraFrameSnapshot> result;
    result.reserve(frameMap.size());

    for (const auto& [cameraId, snapshot] : frameMap) {
        if (snapshot.frame) { // 只返回有帧的
                result.push_back(snapshot);
        }
    }

    return result;

}

void FrameBuffer::clearFrames(){
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& [cameraId, snapshot] : frameMap) {
        snapshot.frame.reset();
        snapshot.timestamp = 0;
    }
}