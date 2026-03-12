#include "business_layer/command/mqtt/mqtt_service.h"


#include "business_layer/command/mqtt_command.h"
#include "business_layer/command/controller.h"

// public

MqttService::~MqttService(){

    stop();

}


void MqttService::start(){
    if(running) return;
    running = true;
    if(!connectBroker())
    {
        std::cerr<<"MQTT connect failed\n";
        return;
    } 
    std::cout<<"MQTT Service "<<std::endl;   
    mqttThread = std::thread(&MqttService::run,this);
}

void MqttService::stop(){  
    
    if(!running) return;

    running = false;

    if(socketFd  > 0){
        auto packet = m_protocol.encodeDisconnect();
        sendPacket(packet);
                     
    }

    if(mqttThread.joinable()){
        mqttThread.join();
    }

    closeConnection();
}

void MqttService::publish(const std::string& topic, std::string& payload){
    auto packet = m_protocol.encodePublish(topic, payload);

    sendPacket(packet);
}

void MqttService::subscribe(const std::string& topic)
{
    static uint16_t packetId = 1;
    auto packet = m_protocol.encodeSubscribe(topic, packetId++);

    sendPacket(packet);
}


// private
 void MqttService::run(){
    std::cout<<"MQTT Service is running..."<<std::endl;
    while(running){
        std::string topic,payload;
        MqttPacket packet = receiveMessage(socketFd,topic,payload);

        handlePacket(packet);
        

    }
    std::cout<<"MQTT Service stopped."<<std::endl;
}
bool MqttService::connectBroker(){  
    socketFd = socket(AF_INET,SOCK_STREAM,0); //创建socket
    if(socketFd < 0){
        std::cerr<<"Failed to create socket\n";
        return false;
    }
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET; //IPv4
    serverAddr.sin_port = htons(port); //端口号
    inet_pton(AF_INET,Ip.c_str(),&serverAddr.sin_addr); //IP地址
    
    if(connect(socketFd,(sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){ //连接服务器
        std::cerr<<"Failed to connect to MQTT broker\n";
        return false;
    }

    //发送CONNECT包
    auto packet = m_protocol.encodeConnect(boxId);

    return sendPacket(packet);
}

bool MqttService::sendPacket(const std::vector<uint8_t>& data){
    if(socketFd < 0) return false;

    ssize_t n = send(socketFd, data.data(), data.size(), 0);

    return n == (ssize_t)data.size();
}


MqttPacket MqttService::receiveMessage(int socketFd,std::string& topic,std::string& payload)
{
    std::vector<uint8_t> buffer(2048);

    ssize_t n = recv(socketFd, buffer.data(), buffer.size(), 0);

    MqttPacket packet;

    if(n <=  0) return packet;

    buffer.resize(n);

    m_protocol.decode(buffer,packet);

    topic = packet.topic;

    payload = packet.payload;

    return packet;
}


void MqttService::handlePacket(const MqttPacket& packet){
    switch(packet.type){
        case MqttPacketType::CONNACK:
        {
            dispatcher.handleMqtt(packet.topic, packet.payload);

            break;
        }

        case MqttPacketType::PINGRESP:
        {
            break;
        }

        case MqttPacketType::SUBACK:
        {
            break;
        }

        default:
            break;
    }
}

void MqttService::closeConnection(){
    
    if(socketFd > 0){

        close(socketFd);

        socketFd = -1;
    }
}