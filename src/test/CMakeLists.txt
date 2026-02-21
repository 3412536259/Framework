cmake_minimum_required(VERSION 3.10)
project(mqtt_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(FRAMEWORK_ROOT ${PROJECT_SOURCE_DIR}/../../..)
set(FRAMEWORK_ROOT "C:/Framework")
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

target_link_directories(mqtt_test PRIVATE
    ${PAHO_MQTT_DIR}/lib
)

if(WIN32)
    target_link_libraries(mqtt_test PRIVATE
        paho-mqttpp3-static
        paho-mqtt3a-static
        paho-mqtt3c-static
        ws2_32
    )
else()
    target_link_libraries(mqtt_test PRIVATE
        paho-mqttpp3-static
        paho-mqtt3a-static
        paho-mqtt3c-static
    )
endif()
