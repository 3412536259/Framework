#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "data_layer/physical_camera/physical_camera.h"
#include "common/config/config_parser.h"
class IStreamService {
    public:
        virtual ~IStreamService() = default;

        virtual void startPullStream() = 0;
        virtual void stopPullStream() = 0;
        virtual void addCamera(std::shared_ptr<PhysicalCamera> camera) = 0;
};

class StreamService : public IStreamService {
    public:
        StreamService();
        ~StreamService() = default;

        // 禁止拷贝
        StreamService(const StreamService&) = delete;
        StreamService& operator=(const StreamService&) = delete;

        void startPullStream();
        void stopPullStream();
        void addCamera(std::shared_ptr<PhysicalCamera> camera);
        bool registerDevices();

    private:
        std::mutex mutex_;
        std::atomic_bool running_ = false;
        std::unordered_map<std::string,std::shared_ptr<PhysicalCamera> > cameras_;
};

