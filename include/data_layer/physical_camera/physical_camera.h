#ifndef PHYSICAL_CAMERA_H
#define PHYSICAL_CAMERA_H

#include <atomic>
#include <memory>
#include "data_layer/physical_camera/frame_queue.h"
#include "data_layer/physical_camera/packet_decoder.h"
#include "data_layer/physical_camera/packet_queue.h"
#include "data_layer/physical_camera/stream_puller.h"
#include "business_layer/stream/frame_dispater.h"
class PhysicalCamera {
    public:
        PhysicalCamera(const std::string& cameraId,
                       const std::string& rtspUrl,
                       std::shared_ptr<FrameQueue> frameQueue,
                       std::shared_ptr<PacketQueue> packetQueue,
                       std::unique_ptr<PacketDecoder> packetDecoder,
                       std::unique_ptr<StreamPuller> streamPuller);
        ~PhysicalCamera();

        void startStreamPull();
        void stopStreamPull();
    
    private:
        void pullLoop();

        FrameData convertToFrameData(AVFrame* frame);
    
    private:
        std::shared_ptr<FrameQueue> frameQueue_;
        std::shared_ptr<PacketQueue> packetQueue_;

        std::unique_ptr<PacketDecoder> packetDecoder_;
        std::unique_ptr<StreamPuller> streamPuller_;

        FrameDispater dispater_;

        std::thread decodeThread_;

        std::string cameraId_;
        std::string rtspUrl_;    
        std::atomic_bool running_ {false};
};

#endif