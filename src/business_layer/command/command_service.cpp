#include "business_layer/command/command_service.h"
CommandService::CommandService(NetworkService* mqttService, CommandDao& cmdDao): m_mqttService(mqttService),commandDao(cmdDao) {}

void CommandService::immitDependence(NetworkService& mqttService){
	m_mqttService = &mqttService;
}


void CommandService::executeCommand(const Command& cmd) {

}

// 实现接口：批量执行待执行命令
void CommandService::executePendingCommands() {

}

// 实现接口：查询本地命令任务状态
CommandState CommandService:: getCommandState(const std::string& cmdId) {

}

// 实现接口：获取指定设备的所有命令状态
DeviceCommands CommandService::getDeviceCommandStates(const std::string& deviceId) {

}

// 实现接口：打开电磁阀
void CommandService::openSolenoidValve(const std::string& deviceId, const std::string& cmdId) {

}

// 实现接口：关闭电磁阀
void CommandService::closeSolenoidValve(const std::string& deviceId, const std::string& cmdId) {

}

// 实现接口：获取摄像头历史视频
std::string CommandService::getCameraHistoryVideo(const std::string& cameraId, const std::string& timeRange) {

}

// 实现接口：MQTT消息接收回调
void CommandService::onMqttMessageReceived(const std::string& topic, const std::string& msg) {

}

// 实现接口：发送命令结果到MQTT云端
void CommandService::sendCommandResultToMqtt(const std::string& cmdId, CommandState state, const std::string& result) {

}

// 实现接口：更新命令状态
void CommandService::updateCommandState(const std::string& cmdId, CommandState newState) {

}


// private
bool CommandService::validateCommand(const Command& cmd){
	
}