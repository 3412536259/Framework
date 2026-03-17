#pragma once

class NetworkService {
public:
    ~NetworkService() = default;

    virtual void  start() = 0;

    virtual void stop() = 0;

    virtual void publish(const std::string& topic,std::string& payload) = 0;
      
    virtual void subscribe(const std::string& topic) = 0;


};