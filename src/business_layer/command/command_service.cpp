#include "business_layer/command/command_service.h"
CommandService::CommandService(NetworkService* mqttService, CommandDao& cmdDao): m_mqttService(mqttService),commandDao(cmdDao) {}

void CommandService::immitDependence(NetworkService& mqttService){
	m_mqttService = &mqttService;
}


void CommandService::executeCommand(const Command& cmd) {
	//既然可以执行那么是可以保存在数据库里面的
	//1.将这个cmd 调用 commandDao 保存在数据库里面
	//2.将这个cmd 的状态变成执行状态，cmd放在缓冲里面去维持这个状态，

}

// 实现接口：批量执行待执行命令
void CommandService::executePendingCommands() {

}

// 实现接口：查询本地命令任务状态（在缓冲里面的）
CommandState CommandService:: getCommandState(const std::string& cmdId) {
	//在缓冲里面的去查看相应的当前命令的状态
}

// 实现接口：获取指定设备的所有命令状态
DeviceCommands CommandService::getDeviceCommandStates(const std::string& deviceId) {
	//在commandDao里面的去查看相应的当前命令的状态
}

CommandState getCommandState(const CommandType& type){
	//在缓冲里面的去查看相应的当前命令的状态
}




// 实现接口：发送命令结果到MQTT云端
void CommandService::sendCommandResultToMqtt(const std::string& topic, const std::string& msg) {
	//调用m_mqttService里面的发布功能
}

// 实现接口：更新命令状态
void CommandService::updateCommandState(const std::string& cmdId, CommandState newState) {

}


// private
bool CommandService::validateCommand(const Command& cmd){
	
}

// 
void CommandService::openSolenoidValve(const CommandType& type) {
	
}

// 
void CommandService::closeSolenoidValve(const CommandType& type) {

}

//
std::string CommandService::getCameraHistoryVideo(const CommandType& type) {

}