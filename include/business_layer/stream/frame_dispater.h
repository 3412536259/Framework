#pragma once

#include <vector>
#include <mutex>
#include "business_layer/lobby/real_time_frame_cache.h"
#include "data_layer/physical_camera/physical_camera_util.h"
class IFrameDispater {
    public:
        virtual ~IFrameDispater() = default;

        virtual bool  onKeyFrame(const AVFrame* frame) = 0; 
};

class FrameDispater : public IFrameDispater {
    public:
        FrameDispater();
        ~FrameDispater();

        bool onKeyFrame(const AVFrame* frame);

        void addConsumer(std::shared_ptr<IFrameConsumer> consumer);

        void dispaterKeyFrame(const KeyFrame& frame);
    
    private:
        std::vector<std::weak_ptr<IFrameConsumer> > consumers_;
        std::mutex mutex_;
};

