#include "business_layer/command/mqtt_command.h"
#include "business_layer/lobby/lobby_service.h"
#include "presentation_layer/http_response.h"
#include <nlohmann/json.hpp>

MQTTCommandController::MQTTCommandController(ILobbyService& lobby) : lobbyService(lobby) {}

HttpResponse MQTTCommandController::handle(const std::string& topic, const std::string& payload) {
    return HttpResponse{}; 
}

void MQTTCommandController::handleMqtt(const std::string& topic, const std::string& payload) {

}



void MQTTCommandController::handleGetRealImage(const nlohmann::json& j){

}



void MQTTCommandController::handleGetAllDeviceStatus(const nlohmann::json& j){

}

void MQTTCommandController::handVideoHistoryTime(const nlohmann::json& j){

}
    
void MQTTCommandController::handVideoHistoryFile(const nlohmann::json& j){

}