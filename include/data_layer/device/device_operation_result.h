#ifndef DEVICE_OPERATION_RESULT_H
#define DEVICE_OPERATION_RESULT_H

#include <string>

class DeviceOperationResult {
    public:
        DeviceOperationResult();
        DeviceOperationResult(int code, const std::string message);
        ~DeviceOperationResult();

    private:
        int code_;
        std::string message_;
};

#endif  