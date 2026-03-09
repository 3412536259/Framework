cmake_minimum_required(VERSION 3.10)
project(mqtt_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # 添加/utf-8编译选项，解决spdlog的编码断言问题
    add_compile_options(/utf-8)
    # 可选：禁用VS的安全警告（避免额外干扰）
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

#set(FRAMEWORK_ROOT ${PROJECT_SOURCE_DIR}/../../..)
set(FRAMEWORK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../)
get_filename_component(FRAMEWORK_ROOT ${FRAMEWORK_ROOT} ABSOLUTE)
message(STATUS "FRAMEWORK_ROOT: ${FRAMEWORK_ROOT}")

set(PAHO_MQTT_DIR ${FRAMEWORK_ROOT}/include/common/mqtt)
set(SPDLOG_DIR ${FRAMEWORK_ROOT}/include/common/spdlog)

add_executable(mqtt_test
    test.cpp
    ../business_layer/command/mqtt_service.cpp
    ../business_layer/command/command_service.cpp
    ../business_layer/command/command_status.cpp
    ../business_layer/command/command_buffer.cpp
    ../common/log/log.cpp
)

target_include_directories(mqtt_test PRIVATE
    ${FRAMEWORK_ROOT}/include
    ${FRAMEWORK_ROOT}/include/common/log
    ${FRAMEWORK_ROOT}/include/business_layer/command
    ${FRAMEWORK_ROOT}/include/business_layer/lobby
    ${FRAMEWORK_ROOT}/src/test
    ${PAHO_MQTT_DIR}/include
    ${SPDLOG_DIR}/include
    
)

if(WIN32)
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
