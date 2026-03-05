#pragma once

class IDeviceManageService {
    public: 

        virtual BoxDeviceStatus getDeviceStatus() = 0;
        virtual BoxDeviceRealTimeData getDeviceRealTimeData() = 0;

        virtual DeviceOperationResult openSolenoidValue(const SolenoidValueInfo& info) = 0;
        virtual DeviceOperationResult closeSolenoidValue(const SolenoidValueInfo& info) = 0;

        virtual DeviceOperationResult controlCarRotation(const CarControl& car) = 0;

        virtual CameraHistoryVideo getCameraHistoryVideo(const CameraInfo& info) = 0;

        virtual RadarPointCloudData getRadarPointCloudData(const RadarInfo& info) = 0;

        virtual BoxConfigResult BoxDeviceParamsConfig( const BoxDeviceParams& params) = 0;

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
        SolenoidInstanceSet _solenoidInstances;

        CameraInstanceSet _cameraInstances;

        SensorInsatnceSet _sensorInstances;

        RadarInstanceSet _radarInstances;

        CarInsatnceSet _carInstances;
};
