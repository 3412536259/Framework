#pragma once

#include "data_layer/box/box_device_status.h"
#include "data_layer/box/box_device_real_time_data.h"
#include "data_layer/device/device_operation_result.h"
#include "data_layer/camera/camera_history_video.h"
#include "data_layer/radar/radar_point_cloud.h"
#include "data_layer/box/box_config_result.h"
#include "data_layer/plc/solenoid_value_info.h"
#include "data_layer/car/car_control.h"
#include "data_layer/camera/camera_info.h"
#include "data_layer/radar/radar_info.h"
#include "data_layer/box/box_device_param.h"

#include "data_layer/box/box_instance.h"
#include "data_layer/plc/solenoid_instance_set.h"
#include "data_layer/sensor/sensor_instance_set.h"
#include "data_layer/camera/camera_instance_set.h"

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
