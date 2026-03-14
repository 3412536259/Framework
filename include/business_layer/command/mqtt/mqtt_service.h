#pragma once
class MQTTCommandController;
class IController;
class IMqttProtocol;
#include "business_layer/command/mqtt/mqtt_object.h"

#include "business_layer/command/mqtt/network_service.h"
#include "business_layer/command/mqtt/protocol.h"
#include <thread>
#include <atomic>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
class MQTTCommandController;
//优化的角度 1.加上消息队列，这样消息发送下来，不能出现堵塞的情况
         // 2.加上重连机制这样当连接断开时，能够自动尝试重新连接MQTT Broker
        //  3.加上心跳机制（简易的），定期发送心跳包以保持连接活跃，并检测连接状态

class IMqttProtocol;
class IController;

class MqttService : public NetworkService{
public:

    MqttService(const std::string& brokerIp, short port,IController& controller,IMqttProtocol& protocol)
        :  Ip(brokerIp),
           port(port),
           socketFd(-1),
           dispatcher(controller),
           m_protocol(protocol)
    {

    }
    ~MqttService();
    
    void start() override;

    void stop();

    void publish(const std::string& topic,std::string& payload);
      
    void subscribe(const std::string& topic);
    
private:
    void run();

    bool connectBroker();

    MqttPacket receiveMessage(int socketFd,std::string& topic,std::string& payload);

    void closeConnection();

    void handlePacket(const MqttPacket& packet);

    bool sendPacket(const std::vector<uint8_t>& data);


    // std::string buildPublishPacket(const std::string& topic,const std::string& payload);

    // void onMessage(const std::string& topic,const std::string& payload);
    
    // void subscribe(const std::string& topic);  //订阅主题
    
    // static void loadingSubscribe(int socketFd);

private:
    std::string boxId = "edge_box";//

    std::string Ip;

    short port;

    int socketFd;

    std::thread mqttThread;

    std::atomic<bool> running;

    IController& dispatcher;

    IMqttProtocol& m_protocol;
};