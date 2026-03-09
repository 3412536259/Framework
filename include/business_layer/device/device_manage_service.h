#pragma once

#include "box_device_status.h"
#include "box_device_real_time_data.h"
#include "device_operation_result.h"
#include "camera_history_video.h"
#include "radar_point_cloud.h"
#include "box_config_result.h"
#include "solenoid_value_info.h"
#include "car_control.h"
#include "camera_info.h"
#include "radar_info.h"
#include "box_device_param.h"

#include "box_instance.h"
#include "solenoid_instance_set.h"
#include "sensor_instance_set.h"
#include "camera_instance_set.h"

class IDeviceManageService {
    public: 

        virtual BoxDeviceStatus getDeviceStatus() = 0;
        virtual BoxDeviceRealTimeData getDeviceRealTimeData() = 0;

        virtual DeviceOperationResult openSolenoidValue(const SolenoidValueInfo& info) = 0;
        virtual DeviceOperationResult closeSolenoidValue(const SolenoidValueInfo& info) = 0;

        virtual DeviceOperationResult controlCarRotation(const CarControl& car) = 0;

        virtual CameraHistoryVideo getCameraHistoryVideo(const CameraInfo& info) = 0;

        virtual RadarPointCloud getRadarPointCloudData(const RadarInfo& info) = 0;

        virtual BoxConfigResult BoxDeviceParamsConfig( const BoxDeviceParam& params) = 0;

};

class DeviceManageService : public IDeviceManageService { 
    public:
        DeviceManageService() = default ;
        ~DeviceManageService() = default;
        BoxDeviceStatus getDeviceStatus() override;
        BoxDeviceRealTimeData getDeviceRealTimeData() override;

        DeviceOperationResult openSolenoidValue(const SolenoidValueInfo& info) override;
        DeviceOperationResult closeSolenoidValue(const SolenoidValueInfo& info) override;

        DeviceOperationResult controlCarRotation(const CarControl& car) override;

        CameraHistoryVideo getCameraHistoryVideo(const CameraInfo& info) override;

        RadarPointCloudData getRadarPointCloudData(const RadarInfo& info) override;

        BoxConfigResult BoxDeviceParamsConfig( const BoxDeviceParams& params) override;

    private:

        BoxInstance boxInstance_;

        SolenoidInstanceSet solenoidInstances_;

        CameraInstanceSet cameraInstances_;

        SensorInstanceSet sensorInstances_;

        // RadarInstanceSet _radarInstances;

        // CarInstanceSet _carInstances;
};
