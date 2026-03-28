#ifndef IFRAME_CONSUMER_H
#define IFRAME_CONSUMER_H

#include "data_layer/physical_camera/physical_camera_util.h"
class IFrameConsumer {
    public:
        virtual ~IFrameConsumer() = default;
        virtual void onFrame(const KeyFrame& frameData) = 0;
};

#endif