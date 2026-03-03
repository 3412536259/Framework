#ifndef WEB_SERVICE_H
#define WEB_SERVICE_H

#include <string>
#include <thread>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "controller.h"

using nlohmann::json;


/**
 * @brief Web服务接口类
 * 提供基于TCP的HTTP JSON接口服务，处理客户端的JSON请求并返回JSON响应
 */
class WebService {
public:
    /**
     * @brief 构造函数
 
     * @param ITaskResultPublisher 任务调度接口指针
     */
    WebService(const std::string& httpPath,short port, HTTPCommandController& controller);

    /**
     * @brief 析构函数
     * 自动停止服务并释放资源
     */
    ~WebService();

    /**
     * @brief 启动Web服务
     * @return 启动成功返回true，失败返回false
     */
    bool start();

    /**
     * @brief 停止Web服务
     * 停止监听、关闭套接字、等待工作线程退出
     */
    void stop();

    // 禁用拷贝构造和赋值运算符（避免线程和套接字资源拷贝问题）
    WebService(const WebService&) = delete;
    WebService& operator=(const WebService&) = delete;

    // 禁用移动构造和赋值运算符（可选，根据实际需求）
    WebService(WebService&&) = delete;
    WebService& operator=(WebService&&) = delete;

private:
    /**
     * @brief 服务运行循环
     * 持续监听客户端连接，处理新连接的接收
     */
    void run();

    /**
     * @brief 处理单个客户端连接
     * @param client_fd 客户端套接字描述符
     */
    void handleClient(int client_fd, const char* client_ip, uint16_t client_port);

    std::string parseRequestBody(const std::string& request, size_t content_length, int client_fd);

    size_t parseContentLength(const std::string& request);
    

    void sendErrorResponse(int client_fd, int status_code, const std::string& message, const json& extra = json{});

    void sendSuccessResponse(int client_fd, const json& response_json);

    std::string getStatusText(int status_code);
    
    // 成员变量
    std::string m_bind_ip;
    HTTPCommandController& m_controller;
    int m_server_fd = -1;                // 服务端套接字描述符（初始化为无效值）
    std::atomic<bool> m_running;          // 服务运行状态标志
    std::thread m_thread;                // 服务运行线程
    uint16_t m_port = 8080;
    
};




#endif // WEB_SERVICE_H