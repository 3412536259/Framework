cmake_minimum_required(VERSION 3.10)

# ========== 核心配置（继承全局） ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==========  外部库的查找路径 ==========
link_directories(/usr/local/lib)


# ========== 源文件列表 ==========
set(SRC_FILES
    # text/sql_test.cpp
    text/comand_test.cpp
    # text/device_service_test.cpp
    # text/text.cpp

    #========== 业务层 ==========

    business_layer/lobby/lobby_service.cpp  #大厅
    business_layer/safety/safety_service.cpp
    business_layer/command/command_service.cpp
    business_layer/timer.cpp 

    business_layer/command/mqtt/protocol.cpp
    business_layer/command/mqtt/mqtt_service.cpp
    business_layer/command/mqtt_command.cpp
    business_layer/command/command_object.cpp   

    business_layer/device/device_acquisition_task.cpp
    business_layer/device/device_manage_service.cpp
    business_layer/device/device_service.cpp
    business_layer/device/device_status_cache.cpp
    business_layer/device/real_time_frame_cache.cpp

    #========== 数据层 ==========
    data_layer/command/command_object.cpp
    data_layer/command/command_dao.cpp

    data_layer/acquisition_task/acquisition_task.cpp
    data_layer/acquisition_task/door_lock_acquisition_task.cpp
    data_layer/acquisition_task/gpio_device_acquisition_task.cpp
    data_layer/acquisition_task/infrared_sensor_acquisition_task.cpp
    data_layer/acquisition_task/infrared_sensor_acquisition_task.cpp
    data_layer/acquisition_task/plc_device_acquisition_task.cpp
    data_layer/acquisition_task/serial_direct_device_acquisition_task.cpp
    data_layer/acquisition_task/smoke_detector_acquisition_task.cpp
    data_layer/acquisition_task/solenoid_acquisition_task.cpp
    data_layer/acquisition_task/water_level_sensor_acquisition_task.cpp
    data_layer/acquisition_task/temp_humid_sensor_acquisition_task.cpp
    data_layer/acquisition_task/camera_acquisition_task.cpp

    data_layer/box/box_config_result.cpp
    data_layer/box/box_device_status.cpp
    data_layer/box/box_instance.cpp

    
    data_layer/camera/camera_history_video.cpp
    data_layer/camera/camera_info.cpp
    data_layer/camera/camera_instance_set.cpp
    data_layer/camera/camera_real_time_frame.cpp
    data_layer/camera/camera_status.cpp
    data_layer/camera/camera.cpp

    data_layer/car/car_control.cpp

    data_layer/device/device_data.cpp
    data_layer/device/device_operation_result.cpp

    data_layer/gpio_device/door_lock_status.cpp
    data_layer/gpio_device/door_lock.cpp
    data_layer/gpio_device/gpio_device_instance_set.cpp
    data_layer/gpio_device/gpio_device_simple_info.cpp

    
    data_layer/plc/plc_device.cpp
    data_layer/plc/plc_instance_set.cpp
    data_layer/plc/plc_instance.cpp

    data_layer/plc_device/infrared_sensor.cpp
    data_layer/plc_device/infrared_sensor.cpp
    data_layer/plc_device/plc_device_info.cpp
    data_layer/plc_device/plc_smoke_detector_status.cpp
    data_layer/plc_device/plc_smoke_detector.cpp
    data_layer/plc_device/plc_water_level_sensor_status.cpp
    data_layer/plc_device/plc_water_level_sensor.cpp
    data_layer/plc_device/solenoid_instance_set.cpp
    data_layer/plc_device/solenoid_real_time_data.cpp
    data_layer/plc_device/solenoid_status.cpp
    data_layer/plc_device/solenoid_value_info.cpp
    data_layer/plc_device/solenoid_value.cpp

    data_layer/radar/radar_info.cpp
    data_layer/radar/radar_point_cloud.cpp
    data_layer/sensor/sensor_instance_set.cpp
    data_layer/sensor/sensor_real_time_data.cpp

    data_layer/sensor/temp_humid_sensor_status.cpp
    data_layer/sensor/temp_humid_sensor.cpp
    data_layer/serial/serial_config.cpp
    data_layer/serial_direct_device/serial_direct_device_instance_set.cpp




    #========== 表现层 ==========

    presentation_layer/http_command.cpp
    presentation_layer/http_service.cpp



    #========== 工具 ==========
    common/log/log.cpp
    common/sqlite/sqlite3.c
    common/sqlite/database_manager.cpp
    # common/sqlite/shell.c //命令行工具的源码
    # main.cpp  # 补充：main函数文件（如果存在，必须添加）
)

# ========== 生成可执行文件 ==========
add_executable(main ${SRC_FILES})

# ========== 头文件路径（关键修复） ==========
target_include_directories(main PUBLIC
    ${ROOT_INCLUDE_DIRS}  # 继承顶层定义的全局头文件路径
    /usr/local/include  # 新增：Paho MQTT 头文件的系统安装路径
)

# ========== 库搜索与链接 ==========
target_link_directories(main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/rknn/3rdparty
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/rknn/utils
    /usr/local/lib  # 新增：指定 Paho 库的系统安装路径
)

target_link_libraries(main PUBLIC
    pthread  # 示例：链接线程库（根据需要添加）
    # 你的其他库：如 rknn_utils、hcnetsdk 等
    paho-mqttpp3   # C++ 库
    paho-mqtt3a    # C 库（异步版）
    paho-mqtt3c    # C 库（同步版）
    pthread dl     # 动态链接库
)

# ========== 测试（必要时注释掉） ==========
# add_subdirectory(test/)