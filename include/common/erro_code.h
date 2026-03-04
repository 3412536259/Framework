#ifndef CODE_H
#define CODE_H

#include <string>
#include <unordered_map>

// 错误码定义命名空间，避免全局命名冲突
namespace ErrorCode {

// 基础错误码（建议按业务模块分段，如 1000-1999 为通用错误，2000-2999 为摄像头/帧查询相关）
enum class Code {
    // 通用成功
    SUCCESS = 0,

    // 通用错误 (1000-1999)
    PARAM_ERROR = 1001,          // 参数错误（格式/类型不正确）
    JSON_PARSE_ERROR = 1002,     // JSON 解析失败
    INVALID_REQUEST = 1003,      // 请求无效（不符合业务规则）
    INTERNAL_SERVER_ERROR = 1004,// 服务器内部错误

    // 摄像头/帧查询相关错误 (2000-2999)
    FRAME_QUERY_INVALID = 2001,  // 帧查询参数无效
    CAMERA_NOT_FOUND = 2002,     // 摄像头不存在
    CAMERA_OFFLINE = 2003,       // 摄像头离线
    FRAME_RETRIEVE_FAILED = 2004,// 帧数据获取失败
    NO_REAL_IMAGE_DATA = 2005    // 无实时图像数据
};

// 错误码与描述信息的映射表
static const std::unordered_map<Code, std::string> CodeMessageMap = {
    {Code::SUCCESS, "操作成功"},
    {Code::PARAM_ERROR, "请求参数错误"},
    {Code::JSON_PARSE_ERROR, "JSON 格式解析失败"},
    {Code::INVALID_REQUEST, "请求无效，不符合业务规则"},
    {Code::INTERNAL_SERVER_ERROR, "服务器内部错误，请稍后重试"},
    {Code::FRAME_QUERY_INVALID, "帧查询参数无效（如缺少摄像头ID、时间范围非法）"},
    {Code::CAMERA_NOT_FOUND, "指定的摄像头不存在"},
    {Code::CAMERA_OFFLINE, "指定的摄像头已离线，无法获取实时帧"},
    {Code::FRAME_RETRIEVE_FAILED, "摄像头帧数据获取失败（如网络异常、设备故障）"},
    {Code::NO_REAL_IMAGE_DATA, "暂无实时图像数据（如摄像头未采集到画面）"}
};

/**
 * @brief 根据错误码获取对应的描述信息
 * @param code 错误码枚举值
 * @return 错误描述字符串，若未找到则返回"未知错误"
 */
inline std::string getMessage(Code code) {
    auto it = CodeMessageMap.find(code);
    return (it != CodeMessageMap.end()) ? it->second : "未知错误";
}

/**
 * @brief 将错误码转换为整数（便于网络传输/JSON序列化）
 * @param code 错误码枚举值
 * @return 错误码对应的整数值
 */
inline int toInt(Code code) {
    return static_cast<int>(code);
}

} // namespace ErrorCode

#endif // CODE_H