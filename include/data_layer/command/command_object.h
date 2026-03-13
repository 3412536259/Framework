#pragma once


struct CommandEntity{
    std::string cmdId;         // 命令唯一ID
    std::string deviceId;      // 设备ID
    CommandType type;          // 命令类型
    CommandState state;        // 命令状态
    std::string content;       // 命令内容
    int64_t createTime;        // 创建时间戳
    int64_t updateTime;        // 更新时间戳

};