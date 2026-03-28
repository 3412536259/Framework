#pragma once

#include "business_layer/device/device_manage_service.h"
#include "business_layer/device/device_status_cache.h"
#include "business_layer/device/device_acquisition_task.h"
#include "business_layer/lobby/real_time_frame_cache.h"
#include "data_layer/camera/camera_real_time_frame.h"
#include "data_layer/serial_direct_device/serial_direct_device_info.h"
#include<thread>
#include<atomic>
#include<mutex>

class IDeviceService{
    public:
        virtual ~IDeviceService() = default;

        virtual BoxDeviceStatus viewAllDeviceStatus() = 0;
        // virtual BoxDeviceRealTimeData getBoxDeviceRealTimeData() = 0;

        //电磁阀控制
        virtual int openSolenoidValue( const PlcDeviceInfo& info) = 0;
        virtual int closeSolenoidValue( const PlcDeviceInfo& info) = 0;
        
        //小车控制
        // virtual DeviceOperationResult controlCarRotation( const CarControl& car) = 0;

        //雷达
        // virtual RadarPointCloud getRadarPointCloudData( const RadarInfo& info) = 0;

        //盒子配置
        // virtual BoxConfigResult configBoxDeviceParams( const BoxDeviceParam& params) = 0;

    

};


class DeviceService : public IDeviceService{
    public: 
        DeviceService(DeviceManageService& deviceManageService,
                      DeviceStatusCache& deviceStatusCache,
                      DeviceAcquisitionTask& deviceAcuqisitionTask,
                      RealTimeFrameCache& realTimeFrameCache);

        ~DeviceService();
        BoxDeviceStatus viewAllDeviceStatus() override;
        // BoxDeviceRealTimeData getBoxDeviceRealTimeData() override;

        //电磁阀控制
        int openSolenoidValue( const PlcDeviceInfo& info) override;
        int closeSolenoidValue( const PlcDeviceInfo& info) override;

        int lockDoorLock(const GPIODeviceSimpleInfo& info);
        int unlockDoorLock(const GPIODeviceSimpleInfo& info);
        
        //小车控制
        // DeviceOperationResult controlCarRotation( const CarControl& car) override;

        //雷达
        // RadarPointCloud getRadarPointCloudData( const RadarInfo& info) override;

        //盒子配置
        // BoxConfigResult configBoxDeviceParams( const BoxDeviceParam& params) override;

        SolenoidStatus getSolenoidValueStatus(const PlcDeviceInfo& info);
        TempHumidSensorStatus getTempHumidSensorStatus(const SerialDirectDeviceInfo& info);
        InfraredSensorStatus getInfraredSensorStatus(const GPIODeviceSimpleInfo& info);
        SmokeDetectorStatus getSmokeDetectorStatus(const GPIODeviceSimpleInfo& info);
        WaterLevelSensorStatus getWaterLevelSensorStatus(const GPIODeviceSimpleInfo& info);

        void updateSolenoidStatus(const SolenoidStatus& status);
        void updateTempHumidSensorStatus(const TempHumidSensorStatus& status);
        void updateInfraredSensorStatus(const InfraredSensorStatus& status);
        void updateSmokeDetectorStatus(const SmokeDetectorStatus& status);
        void updateWaterLevelSensorStatus(const WaterLevelSensorStatus& status);


        void startTimer();
        void stopTimer();

    private:
        //数据采集
        void devicesDataCollection(int deviceType);
        //定时器
        void timerLoop();

        DeviceManageService& deviceManageService_;
        DeviceStatusCache& deviceStatusCache_;
        DeviceAcquisitionTask& deviceAcquisitionTask_;
        RealTimeFrameCache& realTimeFrameCache_;
        
        std::thread _timerThread;
        std::atomic<bool> _running {false};
        std::mutex _mutex;
};