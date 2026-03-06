
class DeviceStatusCache {

    DeviceStatusCache();
    ~DeviceStatusCache();

    public:
        void updateBoxDeviceStatus( const BoxDeviceStatus& devices);
    
        void updateDeviceRealTimeData( const BoxDeviceRealTimeData& data);

        BoxDeviceRealTimeData getBoxRealTimeData() ;

        bool isSolenoidOpen( const SolenoidValueInfo& info);

        bool isSolenoidClose( const SolenoidValueInfo& info);

    private:
        void updateSolenoidStatus( const SolenoidStatus& status);
        void updateSensorStatus( const SensorStatus& status);
        void updateCameraStatus( const CameraStatus& status);

        void updateSolenoidRealTimeData( const SolenoidRealTimeData& data);
        void updateSensorRealTimeData( const SensorRealTimeData& data);

}