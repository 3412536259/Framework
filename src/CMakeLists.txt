cmake_minimum_required(VERSION 3.10)

# ========== 核心配置（继承全局） ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========== 源文件列表 ==========
set(SRC_FILES
    text/text.cpp
    business_layer/lobby/lobby_service.cpp  # 你的业务层代码
    # 如果有main函数，添加：main.cpp
)

# ========== 生成可执行文件 ==========
add_executable(main ${SRC_FILES})

# ========== 头文件路径（关键修复） ==========
target_include_directories(main PUBLIC
    ${ROOT_INCLUDE_DIRS}  # 继承顶层定义的全局头文件路径
    # 补充：如果头文件还有其他路径，在这里添加
    # 例如：${CMAKE_CURRENT_SOURCE_DIR}/other_include
)

# ========== 库搜索与链接 ==========
target_link_directories(main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/rknn/3rdparty
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/rknn/utils
)

target_link_libraries(main PUBLIC
    pthread  # 示例：链接线程库（根据需要添加）
    # 你的其他库：如 rknn_utils、hcnetsdk 等
)