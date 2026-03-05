#include "command_status.h"
#include <string>
#include <iostream>
#include <unordered_map>

// 枚举值转字符串的函数
std::string statusToString(Status status) {
    // 建立枚举值和字符串的映射表
    static const std::unordered_map<Status, std::string> statusMap = {
        {Status::Success, "Success"},
        {Status::Failure, "Failure"},
        {Status::InProgress, "InProgress"},
        {Status::Timeout, "Timeout"},
        {Status::InvalidCommand, "InvalidCommand"},
        {Status::Unauthorized, "Unauthorized"},
        {Status::NotFound, "NotFound"},
        {Status::InternalError, "InternalError"}
    };

    // 查找映射，找不到返回默认值
    auto it = statusMap.find(status);
    if (it != statusMap.end()) {
        return it->second;
    }
    return "UnknownStatus";
}

// 日志初始化工具函数（全局/单例）
void initCommandStatusLogger() {
    try {
        // 只初始化一次logger（spdlog会自动管理单例，重复调用也会返回已存在的logger）
        auto logger = spdlog::basic_logger_mt("command_status_logger", "logs/command_status.log");
        // 禁用缓冲，立即刷盘
        logger->flush_on(spdlog::level::info);
    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Failed to initialize command status logger: " << ex.what() << std::endl;
    }
	std::cerr << "Command status logger initialized successfully." << std::endl;
}

CommandStatus::CommandStatus(Command cmd, Status status, const std::string& message)
{
    _command = cmd;
    _status = status;
    _message = message;
	logStatusChange(); // 构造时记录初始状态
}

void CommandStatus::setStatus(Status status)
{
	_status = status;
	logStatusChange(); // 每次状态改变时记录日志
}

void CommandStatus::logStatusChange()
{
    auto logger = spdlog::get("command_status_logger");
    if (logger) { // 检查logger是否初始化成功
        logger->info(
            "Command status updated | Command: {}, New Status: {}, Message: {}",
            _command.getCommand(),
            statusToString(_status),
            _message
        );
        std::cerr << "Logged command status change: Command: " << _command.getCommand()
                  << ", Status: " << statusToString(_status)
			<< ", Message: " << _message << std::endl;
    }
    else {
        std::cerr << "Logger not initialized. Command: " << _command.getCommand()
                  << ", Status: " << statusToString(_status)
			<< ", Message: " << _message << std::endl;
    }
}

CommandQueue::CommandQueue()
{
	initCommandStatusLogger(); // 初始化日志系统
}

CommandQueue::~CommandQueue()
{
    auto logger = spdlog::get("command_status_logger");
    if (logger) {
        logger->info("CommandQueue is being destroyed, flushing logs...");
        logger->flush(); // 强制刷盘，避免日志丢失
        spdlog::drop("command_status_logger"); // 销毁该logger
    }
}