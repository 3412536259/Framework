#ifndef DEVICE_DATA_H
#define DEVICE_DATA_H

#include "solenoid_status.h"
#include "solenoid_real_time_data.h"
#include "sensor_status.h"
#include "sensor_real_time_data.h"
#include "camera_status.h"
class DeviceData {
    public:
        DeviceData() = default;
        DeviceData(int type,const SolenoidStatus solenoidStatus,const SolenoidRealTimeData SolenoidRealTimeData);
        DeviceData(int type,const Sensorstatus sensorStatus,const SensorRealTimeData sensorRealTimeData);
        DeviceData(int type,const CameraStatus cameraStatus);

        int getType() const ;
        SolenoidStatus getSolenoidStatus() const ;
        SolenoidRealTimeData getSolenoidRealTimeData() const ;

        Sensorstatus getSensorStatus() const ;
        SensorRealTimeData getSensorRealTimeData() const ;

        CameraStatus getCameraStatus() const ;

    
    private:
        int type; // 0: Solenoid, 1: Sensor, 2: Camera

        SolenoidStatus solenoidStatus;
        SolenoidRealTimeData solenoidRealTimeData;

        Sensorstatus sensorStatus;
        SensorRealTimeData sensorRealTimeData;

        CameraStatus cameraStatus;
};

#endif