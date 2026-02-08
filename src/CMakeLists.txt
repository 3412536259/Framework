cmake_minimum_required(VERSION 3.10)
project(video_ai_system LANGUAGES CXX C)

# ========== 核心配置（全局） ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# ========== 变量定义 ==========
set(SRC_FILES
   


)

# ========== 依赖查找 ==========




# ========== 生成可执行文件 ==========
add_executable(main ${SRC_FILES}
    main.cpp


)


# ========== 编译宏定义 ==========
target_compile_definitions(main PUBLIC
    DISABLE_RGA  # 禁用RGA，强制CPU转换
)

# ========== 头文件路径 ==========
target_include_directories(main PUBLIC
    #表现层
    ${PROJECT_SOURCE_DIR}/include/presentation_layer 

    #业务层
    ${PROJECT_SOURCE_DIR}/include/business_layer/serialPort # 串口模块
    ${PROJECT_SOURCE_DIR}/include/business_layer/video  # 视频模块
    ${PROJECT_SOURCE_DIR}/include/business_layer/ai  # AI模块
    ${PROJECT_SOURCE_DIR}/include/business_layer/publisher # 消息发布模块（客服端）
    ${PROJECT_SOURCE_DIR}/include/business_layer/lobby

    # 数据层
    ${PROJECT_SOURCE_DIR}/include/data_layer/video 

    # 公共模块
    ${PROJECT_SOURCE_DIR}/include/common/config
    
)

# ========== 库搜索路径（调整优先级：海康库优先） ==========
target_link_directories(main PUBLIC
    # 1. 海康SDK库（最高优先级）

)



# ========== 链接库（核心调整） ==========
target_link_libraries(main PUBLIC

)
