cmake_minimum_required(VERSION 3.10)

# ========== 核心配置（继承全局） ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========== 编译选项 ==========
add_compile_options(-Wall -Wextra -g)

# ========== 重要路径定义 ==========
set(HIK_OPENSSL_ROOT "/home/ztl/workspace/hklib/hikvision")
set(HIK_SDK_LIB_DIR "${HIK_OPENSSL_ROOT}")
set(HIK_SDK_COM_LIB_DIR "${HIK_OPENSSL_ROOT}/HCNetSDKCom")

# ========== 库搜索路径 ==========
link_directories(
    /usr/local/lib
    ${RKNN_ROOT}/lib
    ${HIK_SDK_LIB_DIR}          # 核心库目录
    ${HIK_SDK_COM_LIB_DIR}      # 组件库目录
)


# ========== 源文件列表 ==========
set(SRC_FILES
    # text/sql_test.cpp
    # text/comand_test.cpp
    # text/ai_test.cpp
    text/device_service_test.cpp
    # text/text.cpp

    #========== 业务层 ==========

    # business_layer/lobby/lobby_service.cpp  #大厅
    # business_layer/lobby/lobby_object.cpp
    
    # business_layer/detection/detection.cpp      #ai

    # business_layer/stream_nvr/camera_manage_service.cpp     #流
    # business_layer/stream_nvr/stream_service.cpp
    # business_layer/stream_nvr/stream_session.cpp
    # business_layer/buffer/frame.cpp
    

    # business_layer/safety/safety_service.cpp
    # business_layer/command/command_service.cpp
    # business_layer/timer.cpp 

    # business_layer/command/mqtt/protocol.cpp
    # business_layer/command/mqtt/mqtt_service.cpp
    # business_layer/command/mqtt_command.cpp
    # business_layer/command/command_object.cpp   

    business_layer/device/device_acquisition_task.cpp
    business_layer/device/device_manage_service.cpp
    business_layer/device/device_service.cpp
    business_layer/device/device_status_cache.cpp
    business_layer/lobby/real_time_frame_cache.cpp
    business_layer/stream/stream_service.cpp
    business_layer/stream/frame_dispater.cpp

    #========== 数据层 ==========
    # data_layer/ai/ai_model_dao.cpp  #ai
    # data_layer/ai/storage_ai.cpp
  
    # data_layer/stream_nvr/puller_hk.cpp #流
    # data_layer/stream_nvr/sdk_init.cpp
    # data_layer/stream_nvr/hik_device_manager.cpp

    # data_layer/command/command_object.cpp
    # data_layer/command/command_dao.cpp

    business_layer/lobby/lobby_object.cpp

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
    data_layer/gpio_device/smoke_detector_status.cpp
    data_layer/gpio_device/smoke_detector.cpp
    data_layer/gpio_device/water_level_sensor_status.cpp
    data_layer/gpio_device/water_level_sensor.cpp
    data_layer/gpio_device/infrared_sensor_status.cpp
    data_layer/gpio_device/infrared_sensor.cpp

    data_layer/physical_camera/frame_queue.cpp
    data_layer/physical_camera/packet_queue.cpp
    data_layer/physical_camera/packet_decoder.cpp
    data_layer/physical_camera/physical_camera.cpp
    data_layer/physical_camera/stream_puller.cpp

    
    data_layer/plc/plc_device.cpp
    data_layer/plc/plc_instance_set.cpp
    data_layer/plc/plc_instance.cpp

    
    data_layer/plc_device/plc_device_info.cpp
    data_layer/plc_device/solenoid_instance_set.cpp
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
    data_layer/serial_direct_device/serial_direct_device_info.cpp




    #========== 表现层 ==========

    # presentation_layer/http_command.cpp
    # presentation_layer/http_service.cpp
    # presentation_layer/http_response.cpp

    #========== 工具 ==========
    # common/log/log.cpp
    # common/log/log_sink.cpp
    # common/log/log_queue.cpp
    # common/log/log_manager.cpp

    # common/sqlite/sqlite3.c
    # common/sqlite/database_manager.cpp

    # common/image_processor/image_processor.cpp

    # common/yolo8/postprocess.cc
    # common/yolo8/yolov8.cc

    common/config/config_parser.cpp #配置
    
    # ../lib/rknn/utils/image_utils.c
    # ../lib/rknn/utils/image_drawing.c
    # ../lib/rknn/utils/file_utils.c
    
    # common/sqlite/shell.c //命令行工具的源码
    # main.cpp  # 补充：main函数文件（如果存在，必须添加）
)

# ========== 生成可执行文件 ==========
add_executable(main ${SRC_FILES})

# include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(main PUBLIC
    ${PROJECT_SOURCE_DIR}/include  # 头文件目录
    ${CMAKE_CURRENT_SOURCE_DIR}/src      # 源码目录
    ${CMAKE_SOURCE_DIR}/lib/rknn/utils       # 工具类
    ${CMAKE_SOURCE_DIR}/
    /usr/local/include
    /usr/local/lib
    ${STB_INCLUDES}
    ${LIBJPEG_INCLUDES}
    ${LIBRKNNRT_INCLUDES}
    ${LIBRGA_INCLUDES}
    ${LIBSNDFILE_INCLUDES}
    ${LIBFFTW_INCLUDES}

    ${HIKVISION_INCLUDE_DIR}/include 

)
#========== 依赖库查找 ==========
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED libavformat libavcodec libswscale libavutil)
find_package(JPEG REQUIRED)

# 把FFmpeg、JPEG头文件加入
target_include_directories(main PUBLIC
    ${FFMPEG_INCLUDE_DIRS}
    ${CMAKE_INSTALL_PREFIX}/lib
    ${JPEG_INCLUDE_DIR}
)

# ========== 链接所有库（关键：海康SDK已加入） ==========
target_link_libraries(main
    # 系统基础
    pthread
    dl
    rt

    # 三方库
    ${FFMPEG_LIBRARIES}
    ${JPEG_LIBRARIES}
    turbojpeg

    # RKNN
    rknnrt
    rga
    drm

    # MQTT
    paho-mqttpp3
    paho-mqtt3a
    paho-mqtt3c

    # 海康SDK（必须按这个顺序链接）
    hcnetsdk 
    PlayCtrl 
    SuperRender 
    AudioRender 
    hpr 
    analyzedata
    AudioIntercom 
    HCAlarm 
    HCCoreDevCfg 
    HCDisplay 
    HCGeneralCfgMgr
    HCIndustry 
    HCPlayBack 
    HCPreview 
    HCVoiceTalk 
    StreamTransClient
    SystemTransform
    z
)
# ========== 测试（必要时注释掉） ==========
# add_subdirectory(test/)