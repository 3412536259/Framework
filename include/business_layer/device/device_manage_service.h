#pragma once

#include "data_layer/box/box_device_status.h"
#include "data_layer/device/device_operation_result.h"
#include "data_layer/camera/camera_history_video.h"
#include "data_layer/radar/radar_point_cloud.h"
#include "data_layer/box/box_config_result.h"
#include "data_layer/car/car_control.h"
#include "data_layer/camera/camera_info.h"
#include "data_layer/radar/radar_info.h"
#include "data_layer/box/box_device_param.h"

#include "data_layer/box/box_instance.h"
#include "data_layer/camera/camera_instance_set.h"
#include "data_layer/plc/plc_instance_set.h"
#include "data_layer/gpio_device/gpio_device_instance_set.h"
#include "data_layer/serial_direct_device/serial_direct_device_instance_set.h"

class IDeviceManageService {
    public: 

        virtual BoxDeviceStatus getDeviceStatus() = 0;
        // virtual BoxDeviceRealTimeData getDeviceRealTimeData() = 0;

        virtual int openSolenoidValue(const PlcDeviceInfo& info) = 0;
        virtual int closeSolenoidValue(const PlcDeviceInfo& info) = 0;

        // virtual DeviceOperationResult controlCarRotation(const CarControl& car) = 0;

        // virtual RadarPointCloud getRadarPointCloudData(const RadarInfo& info) = 0;

        // virtual BoxConfigResult BoxDeviceParamsConfig( const BoxDeviceParam& params) = 0;

        // 设备数据采集，返回DeviceData的列表，deviceType: 0-电磁阀, 1-传感器, 2-摄像头,3-门锁
        virtual std::vector<DeviceData> deviceDataAcquisition(int deviceType) = 0; 

};

class DeviceManageService : public IDeviceManageService { 
    public:
        DeviceManageService() = default ;
        ~DeviceManageService() ;
        DeviceManageService(
                            PlcInstanceSet&& plcInstances,
                            GPIODeviceInstanceSet&& gpioInstanceSet,
                            SerialDirectDeviceInstanceSet&& serialInstances);
        DeviceManageService(DeviceManageService&&) = default;
        DeviceManageService& operator=(DeviceManageService&&) = default;
        DeviceManageService(const DeviceManageService&) = delete;
        DeviceManageService& operator=(const DeviceManageService&) = delete;

        BoxDeviceStatus getDeviceStatus() override;
        SolenoidStatus querySolenoidValueStatus(const PlcDeviceInfo& info);
        TempHumidSensorStatus queryTempHumidSensorStatus(const std::string& deviceId);
        InfraredSensorStatus queryInfraredSensorStatus(const std::string& deviceId);
        SmokeDetectorStatus querySmokeDetectorStatus(const std::string& deviceId);
        WaterLevelSensorStatus queryWaterLevelSensorStatus(const std::string& deviceId);

        int openSolenoidValue(const PlcDeviceInfo& info) override;
        int closeSolenoidValue(const PlcDeviceInfo& info) override;

        int lockDoorLock(const GPIODeviceSimpleInfo& info);
        int unlockDoorLock(const GPIODeviceSimpleInfo& info);

        std::vector<DeviceData> deviceDataAcquisition(int deviceType) override;

        // DeviceOperationResult controlCarRotation(const CarControl& car) override;
        // BoxDeviceRealTimeData getDeviceRealTimeData() override;
        // RadarPointCloud getRadarPointCloudData(const RadarInfo& info) override;

        // BoxConfigResult boxDeviceParamsConfig( const BoxDeviceParams& params) override;

    private:

      

        PlcInstanceSet plcInstances_;

        GPIODeviceInstanceSet gpioInstanceSet_;

        SerialDirectDeviceInstanceSet serialInstances_;

        // CameraInstanceSet cameraInstances_;

        // BoxInstance boxInstance_;
        // RadarInstanceSet _radarInstances;
        // CarInstanceSet _carInstances;
};
