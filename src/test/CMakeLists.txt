cmake_minimum_required(VERSION 3.10)
project(mqtt_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(FRAMEWORK_ROOT ${PROJECT_SOURCE_DIR}/../../..)
if(WIN32)
    set(FRAMEWORK_ROOT "C:/Framework")
else()
    # Linux 下 Framework 的路径（替换成你远程 Linux 机器上的实际路径）
    set(FRAMEWORK_ROOT "/home/mokna/Framework")
endif()
set(PAHO_MQTT_DIR ${FRAMEWORK_ROOT}/include/common/mqtt)

add_executable(mqtt_test
    test.cpp
    ../business_layer/command/mqtt_service.cpp
    ../business_layer/command/command_service.cpp
)

target_include_directories(mqtt_test PRIVATE
    ${FRAMEWORK_ROOT}/include
    ${FRAMEWORK_ROOT}/include/business_layer/command
    ${FRAMEWORK_ROOT}/include/business_layer/lobby
    ${FRAMEWORK_ROOT}/src/test
    ${PAHO_MQTT_DIR}/include
    
)

if(WIN32)
    # Windows 链接配置
    target_link_directories(mqtt_test PRIVATE
        ${PAHO_MQTT_DIR}/lib
    )
    target_link_libraries(mqtt_test PRIVATE
        paho-mqttpp3-static
        paho-mqtt3a-static
        paho-mqtt3c-static
        ws2_32
    )
else()
    # Linux 链接配置（补充 pthread，Linux 下 MQTT 库依赖线程库）
    # 关键：设置运行时库搜索路径（RPath）
    set_target_properties(mqtt_test PROPERTIES
        INSTALL_RPATH "/usr/local/lib"
        BUILD_WITH_INSTALL_RPATH ON
    )
    target_link_libraries(mqtt_test PRIVATE
        paho-mqttpp3
        paho-mqtt3a
        paho-mqtt3c
        pthread
        dl
    )
    
endif()
