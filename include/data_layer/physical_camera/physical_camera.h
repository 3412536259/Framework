#ifndef PHYSICAL_CAMERA_H
#define PHYSICAL_CAMERA_H

#include <atomic>
#include <memory>
#include <deque>
extern "C" {
    #include <libavutil/imgutils.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

#include "data_layer/physical_camera/frame_queue.h"
#include "data_layer/physical_camera/packet_decoder.h"
#include "data_layer/physical_camera/packet_queue.h"
#include "data_layer/physical_camera/stream_puller.h"
#include "business_layer/stream/frame_dispater.h"
class PhysicalCamera {
    public:
        PhysicalCamera(const std::string& cameraId,
                       const std::string& rtspUrl,
                       std::shared_ptr<PacketQueue> packetQueue,
                       std::unique_ptr<PacketDecoder> packetDecoder,
                       std::unique_ptr<StreamPuller> streamPuller);
        ~PhysicalCamera();

        std::string getCameraId() {return cameraId_;}

        void startStreamPull();
        void stopStreamPull();
    
    private:
        void pullLoop();
        void storePacket(const VideoPacket& pkt);
        void recordLoop();
        void generateHistoryVideo();
        int64_t nowMs();

        // PhysicalFrameData convertToFrameData(AVFrame* frame);

        // PixelFormat convertPixelFormat(AVPixelFormat format); 
    
    private:
        std::shared_ptr<PacketQueue> packetQueue_;

        std::unique_ptr<PacketDecoder> packetDecoder_;
        std::unique_ptr<StreamPuller> streamPuller_;

        FrameDispater dispater_;

        std::thread decodeThread_;

        std::thread recordThread_;
        std::mutex recordMutex_;

        std::deque<VideoPacket> videoPacketBuffer_;
        std::mutex bufferMutex_;
        const int MAX_BUFFER_MS = 1 * 60 * 1000;

        std::string cameraId_;
        std::string rtspUrl_;    
        std::atomic_bool running_ {false};
};

#endif