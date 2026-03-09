#pragma once

#include "data_layer/plc/solenoid_status.h"
#include "data_layer/sensor/sensor_status.h"
#include "data_layer/camera/camera_status.h"
#include "data_layer/plc/solenoid_real_time_data.h"
#include "data_layer/sensor/sensor_real_time_data.h"
#include<unordered_map>
#include<memory>
#include<vector>

class DeviceStatusCache {

    DeviceStatusCache();
    ~DeviceStatusCache();

    public:

        void updateBoxDeviceStatus( const BoxDeviceStatus& devices);
        void updateDeviceStatus( const std::vector<std::unique_ptr<DeviceData> >& deviceDataList );

        void updateBoxDeviceRealTimeData( const BoxDeviceRealTimeData& data);
        void updateDeviceRealTimeData( const std::vector<std::unique_ptr<DeviceData> >& deviceDataList );

        BoxDeviceStatus getBoxDeviceStatus();

        BoxDeviceRealTimeData getBoxDeviceRealTimeData() ;

        bool isBoxDeviceStatusEmpty();
        bool isBoxRealTimeDataEmpty();

        bool isSolenoidOpen( const SolenoidValueInfo& info);
        bool isSolenoidClose( const SolenoidValueInfo& info);

    private:
        void updateSolenoidStatus( const SolenoidStatus& status);
        void updateSensorStatus( const SensorStatus& status);
        void updateCameraStatus( const CameraStatus& status);

        void updateSolenoidRealTimeData( const SolenoidRealTimeData& data);
        void updateSensorRealTimeData( const SensorRealTimeData& data);

        std::unordered_map<std::string, std::unique_ptr<SolenoidStatus> > _solenoidStatusMap;
        std::unordered_map<std::string, std::unique_ptr<SensorStatus> > _sensorStatusMap;
        std::unordered_map<std::string, std::unique_ptr<CameraStatus> > _cameraStatusMap;
        // std::unordered_map<std::string, std::unique_ptr<RadarStatus> > _radarStatusMap;
        // std::unordered_map<std::string, std::unique_ptr<CarStatus> > _carStatusMap;

        std::unordered_map<std::string, std::unique_ptr<SolenoidRealTimeData> > _solenoidRealTimeDataMap;
        std::unordered_map<std::string, std::unique_ptr<SensorRealTimeData> > _sensorRealTimeDataMap;
        // std::unordered_map<std::string, std::unique_ptr<CameraRealTimeData> > _cameraRealTimeDataMap;
        // std::unordered_map<std::string, std::unique_ptr<RadarRealTimeData> > _radarRealTimeDataMap;
        // std::unordered_map<std::string, std::unique_ptr<CarRealTimeData> > _carRealTimeDataMap;

};

