#pragma once

#include <memory>
#include <queue>
#include <unordered_map>
//使用mqtt的发布功能
#include "business_layer/command/mqtt/protocol.h"
#include "data_layer/command/command_dao.h"
#include "business_layer/command/command_object.h"

class NetworkService;
 
//命令执行 ，命令状态获取 ，命令生命周期管理
class ICommandService {
public:

	virtual ~ICommandService() = default;
	
	// 执行指定命令（文档中"构建命令对象并执行命令"）
	virtual void executeCommand(const Command& cmd) = 0;

	// 批量执行待执行命令（适配MQTT批量消息）
	virtual void executePendingCommands() = 0;

	// 查询本地命令任务状态（按命令ID）
	virtual CommandState getCommandState(const std::string& cmdId) = 0; 

	// 获取指定设备的所有命令任务状态（按设备ID，文档"获取当前设备任务的状态"）
	virtual DeviceCommands getDeviceCommandStates(const std::string& deviceId) = 0;

	//实现接口：查看那种类型的命令状态
	virtual CommandState getCommandState(const CommandType& type) = 0;

	// 发送命令结果到MQTT（文档中"将消息发送出去，上报执行结果"）
	virtual void sendCommandResultToMqtt(const std::string& topic, const std::string& msg) = 0;

	// 更新命令状态（执行后同步状态到DAO和内存）
	virtual void updateCommandState(const std::string& cmdId, CommandState newState) = 0;
};


class CommandService : public ICommandService
{
public:
	CommandService(NetworkService* mqttService, CommandDao& cmdDao);
	~CommandService() = default;

	// 注入MQTT网络服务（动态替换，适配扩展）
	void immitDependence(NetworkService& mqttService);

    // 实现接口：执行指定命令
    void executeCommand(const Command& cmd) override;

    // 实现接口：批量执行待执行命令
    void executePendingCommands() override;

    // 实现接口：查询正在执行命令任务状态
    CommandState getCommandState(const std::string& cmdId) override;

    // 实现接口：获取指定设备的所有命令状态
    DeviceCommands getDeviceCommandStates(const std::string& deviceId) override;

    //实现接口：查看那种类型的命令状态
	CommandState getCommandState(const CommandType& type) override;


    // 实现接口：发送命令结果到MQTT
    void sendCommandResultToMqtt(const std::string& topic, const std::string& msg) override;

    // 实现接口：更新命令状态
    void updateCommandState(const std::string& cmdId, CommandState newState) override;


private:
	
	// 私有辅助方法：校验命令合法性（联动安全服务，文档中安全验证）
    bool validateCommand(const Command& cmd);

	// 
    void openSolenoidValve(const CommandType& type) ;

    // 
    void closeSolenoidValve(const CommandType& type) ;

    // 
    std::string getCameraHistoryVideo(const CommandType& type) ;

private:



	NetworkService* m_mqttService; // MQTT网络服务（文档中mqtt连接封装类）

	CommandDao& commandDao;	// 命令DAO（文档中命令存储，持久化）

	std::unordered_map<std::string, Command> commandCache;  // 内存级命令缓存（维护当前执行/待执行命令，文档中命令状态维护）
	// 扩展预留：生产者消费者队列（文档中"扩展将加入缓冲，构建接收/发送队列"）
    std::queue<Command> m_mqttRecvQueue;  // MQTT接收队列
    std::queue<Command> m_mqttSendQueue;  // MQTT发送队列
};


