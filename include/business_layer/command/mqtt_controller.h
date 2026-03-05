#include "presentation_layer/controller.h"


class MQTTCommandController : public IController{
public:
    
    explicit MQTTCommandController(ILobbyService& lobby);
    
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

    // void handleGetSensorData(const nlohmann::json& j);

    void handleGetAllDeviceStatus(const nlohmann::json& j);

    void handVideoHistoryTime(const nlohmann::json& j);
    
    void handVideoHistoryFile(const nlohmann::json& j);


    // void
};