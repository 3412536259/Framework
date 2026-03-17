#pragma once

#include "business_layer/device/device_manage_service.h"
#include "business_layer/device/device_status_cache.h"
#include "business_layer/device/device_acquisition_task.h"
#include "business_layer/device/real_time_frame_cache.h"

#include "data_layer/camera/camera_real_time_frame.h"

#include<thread>
#include<atomic>
#include<mutex>

class IDeviceService{
    public:
        virtual ~IDeviceService() = default;

        virtual BoxDeviceStatus viewAllDeviceStatus() = 0;
        virtual BoxDeviceRealTimeData getBoxDeviceRealTimeData() = 0;

        //电磁阀控制
        virtual DeviceOperationResult openSolenoidValue( const SolenoidValueInfo& info) = 0;
        virtual DeviceOperationResult closeSolenoidValue( const SolenoidValueInfo& info) = 0;
        
        //小车控制
        virtual DeviceOperationResult controlCarRotation( const CarControl& car) = 0;
        
        //摄像头
        virtual CameraRealTimeFrame getCameraRealTimeFrame( const CameraInfo& info) = 0;
        virtual CameraHistoryVideo viewCameraHistoryVideo( const CameraInfo& info) = 0;

        //雷达
        virtual RadarPointCloud getRadarPointCloudData( const RadarInfo& info) = 0;

        //盒子配置
        virtual BoxConfigResult configBoxDeviceParams( const BoxDeviceParam& params) = 0;

    

};


class DeviceService : public IDeviceService{
    public: 
        DeviceService(IDeviceManageService& deviceManageService,
                      DeviceStatusCache& deviceStatusCache,
                      DeviceAcquisitionTask& deviceAcuqisitionTask,
                      RealTimeFrameCache& realTimeFrameCache);

        ~DeviceService();
        BoxDeviceStatus viewAllDeviceStatus() override;
        BoxDeviceRealTimeData getBoxDeviceRealTimeData() override;

        //电磁阀控制
        DeviceOperationResult openSolenoidValue( const SolenoidValueInfo& info) override;
        DeviceOperationResult closeSolenoidValue( const SolenoidValueInfo& info) override;
        
        //小车控制
        DeviceOperationResult controlCarRotation( const CarControl& car) override;
        
        //摄像头
        CameraRealTimeFrame getCameraRealTimeFrame( const CameraInfo& info) override;
        CameraHistoryVideo viewCameraHistoryVideo( const CameraInfo& info) override;

        //雷达
        RadarPointCloud getRadarPointCloudData( const RadarInfo& info) override;

        //盒子配置
        BoxConfigResult configBoxDeviceParams( const BoxDeviceParam& params) override;

        void startTimer();
        void stopTimer();

    private:
        //数据采集
        void devicesDataCollection(int deviceType) override;
        //定时器
        void timerLoop();

        DeviceStatusCache& deviceStatusCache_;

        DeviceManageService& deviceManageService_;
        
        DeviceAcquisitionTask& deviceAcquisitionTask_;

        RealTimeFrameCache& realTimeFrameCache_;

        std::thread _timerThread;
        std::atomic<bool> _running {false};
        std::mutex _mutex;
};