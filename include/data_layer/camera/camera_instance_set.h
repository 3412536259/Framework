#ifndef CAMERA_INSTANCE_SET_H
#define CAMERA_INSTANCE_SET_H

#include "camera_status.h"
#include "camera.h"
#include "camera_history_video.h"
#include "device_data.h"
#include <unordered_map>
#include <memory>
#include <vector>

class CameraInstanceSet {
    public:
        CameraInstanceSet() = default;
        CameraInstanceSet(const std::unordered_map<std::string, std::unique_ptr<Camera> >& cameras);
        ~CameraInstanceSet();

        const std::vector<CameraStatus> getCameraStatusList() const;

        CameraHistoryVideo getCameraHistoryVideo(const std::string& cameraId) const;

        std::vector<std::unique_ptr<DeviceData> > acquisitionCameraData();

    private:
        std::unordered_map<std::string, std::unique_ptr<Camera> > cameras_; 
};

#endif