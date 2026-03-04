#include "presentation_layer/controller.h"

HTTPCommandController::HTTPCommandController(ILobbyService& lobby) : lobbyService(lobby) {
    // 构造函数，初始化lobbyService引用
}
// public:

void HTTPCommandController::handle(const std::string& topic, const std::string& payload){
    
}

// private:

void HTTPCommandController::handleGetRealImage(const nlohmann::json& j){
    
}

void HTTPCommandController::handleGetSensorData(const nlohmann::json& j){

}

void HTTPCommandController::handleGetAllDeviceStatus(const nlohmann::json& j){

}

void HTTPCommandController::handVideoHistory(const nlohmann::json& j){

}
    
void HTTPCommandController::handVideoHistoryFile(const nlohmann::json& j){

}