cmake_minimum_required(VERSION 3.10)

# ========== 核心配置（继承全局） ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==========  外部库的查找路径 ==========
link_directories(/usr/local/lib)


# ========== 源文件列表 ==========
set(SRC_FILES
    text/text.cpp
    #========== 业务层 ==========

    business_layer/lobby/lobby_service.cpp  # 你的业务层代码

    #========== 数据层 ==========


    #========== 表现层 ==========
    presentation_layer/http_command.cpp
    presentation_layer/http_service.cpp

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
)

# ========== 测试（必要时注释掉） ==========
add_subdirectory(test/)