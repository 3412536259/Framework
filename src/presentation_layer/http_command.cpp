#include "presentation_layer/controller.h"

HTTPCommandController::HTTPCommandController(ILobbyService& lobby) : lobbyService(lobby) {
    // 构造函数，初始化lobbyService引用
}
// public:

void HTTPCommandController::handle(const std::string& topic, const std::string& payload){
    if(topic == GET_REAL_IMAGE_TOPIC){
        nlohmann::json j = nlohmann::json::parse(payload);
        handleGetRealImage(j);  
        
    }
}

// private:

void HTTPCommandController::handleGetRealImage(const nlohmann::json& j){
    FrameQuery query(j);
    if(!query.isValid()){
        // 处理无效查询，例如返回错误响应
        return;
    }
    lobbyService.retrieveLiveCameraFrame(query);
}

// void HTTPCommandController::handleGetSensorData(const nlohmann::json& j){

// }

void HTTPCommandController::handleGetAllDeviceStatus(const nlohmann::json& j){
    DeviceStatusQuery query(j);
    if(!query.isValid()){
        // 处理无效查询，例如返回错误响应
        return;
    }
    lobbyService.retrieveDeviceStatus(query);   
}

void HTTPCommandController::handVideoHistoryTime(const nlohmann::json& j){
    HistoricalVideoQuery query(j);
    if(!query.isValid()){
        // 处理无效查询，例如返回错误响应
        return;
    }
    lobbyService.retrieveHistoricalCameraFootage(query);    
}
    
void HTTPCommandController::handVideoHistoryFile(const nlohmann::json& j){
    DownloadHistoricalVideo download(j);
    if(!download.isValid()){
        // 处理无效查询，例如返回错误响应
        return;
    }
    lobbyService.downloadHistoricalCameraFootage(download);     
}