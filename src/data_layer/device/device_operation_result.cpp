#include "device_operation_result.h"

DeviceOperationResult::DeviceOperationResult() {

}

DeviceOperationResult::DeviceOperationResult(int code, const std::string message)
    : code_(code), message_(message) {

}

DeviceOperationResult::~DeviceOperationResult() {

}