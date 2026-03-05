#include "device_status_cache.h"

class DeviceStatusCache {
    public: 
        DeviceStatusCache() : _ status() {}

    private:
        BoxDeviceStatus _status;
}