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
        std::cout<<"MQTT Service is not"<<std::endl; 
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
    std::lock_guard<std::mutex> lock(sendMutex);
    if(socketFd < 0) return false;

    size_t total = 0;

    while(total < data.size()){
        ssize_t n = send(socketFd, data.data() + total, data.size() - total, 0);

        if(n <= 0){
            if(errno == EAGAIN || errno == EWOULDBLOCK){
                // 需要等待可写（select/epoll）
            }   
            return false;
        }

        total += n;
    }

    return true;  // ✅ 只要循环发完就是成功
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
            std::cout << "MQTT Connected!\n";
            // ✅ 在这里订阅所有主题
            subscribe(boxId + "OPERATE_PLC_WITH_VERIFY_TOPIC");//电磁阀
            subscribe(boxId + "UPDATE_CONFIG_TOPIC");//配置更新
            subscribe(boxId + "GET_ALL_DEVICE_STATUS_TOPI");   //设备的状态
            break;
        }
        case MqttPacketType::PUBLISH:
        {   
            std::cout << "recv topic: " << packet.topic << std::endl;
            std::cout << "payload: " << packet.payload << std::endl;
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