#include "business_layer/stream_nvr/stream_session.h"

StreamSession::StreamSession(const CameraInfo& info,std::shared_ptr<FrameBuffer> buffer,const std::string brand,std::shared_ptr<NVRLoginManager> nvrLogin)
    : info_(info),
      frameBuffer_(buffer),
      running_(false)
{
    puller_ = PullerFactory::create(brand);
    
    recordOperator_ = RecordFactory::create(brand);
}

StreamSession::~StreamSession(){

}

bool StreamSession::start() {
    if (running_) {
        return false; // 已经在跑
    }

    running_ = true;
    
    worker_ = std::thread([this]() {
        // 1. 初始化
        if (!puller_->open()) {
            running_ = false;
            return;
        }
        //2. 打开流
        if(!puller_->start()){
            running_ = false;
            return;
        }
        //3. 拉取流
        while (running_) {
            auto frame = puller_->getLatestFrame();

            if (!frame) {
                // 这里不要直接退出（网络抖动很常见）
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            // 4.. 只保留关键帧
            //把帧放在frameBuffer_里面
            frameBuffer_->updateFrame(info_,frame);
        }

        // 5. 关闭流
        puller_->stop();
    });

    return true;
}
bool StreamSession::stop() {
    if (!running_) {
        return false;
    }
    
    running_ = false;

    puller_->close();


    if (worker_.joinable()) {
        worker_.join();  
    }

    return true;
}