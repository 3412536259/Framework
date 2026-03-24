#include "data_layer/physical_camera/physical_camera.h"

PhysicalCamera::PhysicalCamera(const std::string& cameraId,
                       const std::string& rtspUrl,
                       std::shared_ptr<FrameQueue> frameQueue,
                       std::shared_ptr<PacketQueue> packetQueue,
                       std::unique_ptr<PacketDecoder> packetDecoder,
                       std::unique_ptr<StreamPuller> streamPuller)
    : cameraId_(cameraId),
      rtspUrl_(rtspUrl),
      frameQueue_(std::move(frameQueue)),
      packetQueue_(std::move(packetQueue)),
      packetDecoder_(std::move(packetDecoder)),
      streamPuller_(std::move(streamPuller)),
      running_(false) {
    streamPuller_ -> setPacketQueue(packetQueue_);
}

PhysicalCamera::~PhysicalCamera() {

}

void PhysicalCamera::startStreamPull() {
    if(running_) return ;

    running_ = true;

    

    if(!streamPuller_ -> open()) {
        running_ = false;
        return ;
    }

    streamPuller_ -> start();

    decodeThread_ = std::thread(&PhysicalCamera::pullLoop,this);

}
void PhysicalCamera::stopStreamPull() {
    if(!running_) return;

    running_ = false;

    streamPuller_ -> stop();

    packetQueue_ -> stop();
    frameQueue_ -> stop();

    if(decodeThread_.joinable())
        decodeThread_.join();
    
    packetQueue_ -> clear();
    frameQueue_ -> clear();

    packetDecoder_ -> flush();
}
    
 
void PhysicalCamera::pullLoop() {
    while (running_) {
        AVPacket packet;

        if(!packetQueue_ -> pop(packet))
            continue;

        std::vector<AVFrame*> frames;
        if(!packetDecoder_ -> decode(&packet,frames))
            continue;
        
        for(auto* frame : frames) {
            frameQueue_ -> push(frame);

            FrameData frameData = convertToFrameData(frame);

            if(dispater_.onKeyFrame(frameData)) {
                dispater_.dispaterKeyFrame(frameData);
            }
        }

        av_packet_unref(&packet);
    }
    
}