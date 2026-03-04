#pragma once
#include <string>
#include "business_layer/lobby/lobby_service.h"
#include <nlohmann/json.hpp>
using nlohmann::json;
class IController{
public:

    virtual void handle(const std::string& topic, const std::string& payload) = 0;

    virtual ~IController() = default;
};

/**
 * @brief Web控制器接口类
 * 处理JSON请求的业务逻辑，与WebService解耦
 */

class HTTPCommandController : public IController{
public:
    
    explicit HTTPCommandController(ILobbyService& lobby);////这样需要改变一下，加上lobby大厅，

    
    /**
     * @brief 处理JSON请求
     * @param topic 处理请求
     * @return payload 响应数据
     */
    void handle(const std::string& topic, const std::string& payload) override;
private:
    ILobbyService& lobbyService; 

private:

    void handleGetRealImage(const nlohmann::json& j);

    void handleGetSensorData(const nlohmann::json& j);

    void handleGetAllDeviceStatus(const nlohmann::json& j);

    void handVideoHistory(const nlohmann::json& j);
    
    void handVideoHistoryFile(const nlohmann::json& j);


    // void
};
