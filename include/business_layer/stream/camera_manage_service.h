#pragma

#include <vector>
#include <string>
#include <unordered_map>
#include "data_layer/physical_camera/physical_camera.h"
class ICameraManageService {
    public:
        virtual ~ICameraManageService() = default;

        virtual bool startPullStream() = 0;
        virtual bool stopPullStream() = 0;
};

class CameraManageService : public ICameraManageService {
    public:
        CameraManageService(std::vector<PhysicalCamera> cameras);
        ~CameraManageService() = default;

        bool startPullStream();
        bool stopPullStream();

    private:
        std::unordered_map<std::string,PhysicalCamera> cameras_;
};

