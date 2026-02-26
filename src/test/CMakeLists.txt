cmake_minimum_required(VERSION 3.10)
project(mqtt_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(FRAMEWORK_ROOT ${PROJECT_SOURCE_DIR}/../../..)
set(FRAMEWORK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../)
get_filename_component(FRAMEWORK_ROOT ${FRAMEWORK_ROOT} ABSOLUTE)
message(STATUS "FRAMEWORK_ROOT: ${FRAMEWORK_ROOT}") 
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
