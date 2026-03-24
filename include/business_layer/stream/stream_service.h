#pragma once

#include "business_layer/stream/camera_manage_service.h"
class IStreamService {
    public:
        virtual ~IStreamService() = default;

        virtual void startStreamPull() = 0;
        virtual void stopStreamPull() = 0;

};

class StreamService : public IStreamService{
    public:
        StreamService(CameraManageService& cameraManageService_);
        ~StreamService();

        void startStreamPull();
        void stopStreamPull();

    private:
        CameraManageService cameraManageService_;
};
