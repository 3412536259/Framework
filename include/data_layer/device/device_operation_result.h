#ifndef DEVICE_OPERATION_RESULT_H
#define DEVICE_OPERATION_RESULT_H

#include <string>

class DeviceOperationResult {
    public:
        DeviceOperationResult() = default;
        DeviceOperationResult(int code, const std::string message);

    private:
        int code_;
        std::string message_;
};

#endif  