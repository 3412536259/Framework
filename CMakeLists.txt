cmake_minimum_required(VERSION 3.10)
project(HikSdkDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_SOC "rk3568" CACHE STRING "Target SOC for RKNN")
set(CMAKE_SYSTEM_NAME "Linux" CACHE STRING "Target system")

# ========== 全局配置 ==========
# 定义全局头文件路径（让子目录继承）
set(ROOT_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include          # 外部头文件目录
    ${CMAKE_CURRENT_SOURCE_DIR}/src              # src目录自身（关键：解决src下的头文件引用）
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/inih # 第三方依赖（如果有）
    CACHE INTERNAL "Global include directories"
)

# 全局宏定义（替代 add_definitions，更现代）
add_compile_definitions(DISABLE_RGA)
message(STATUS "⚠️ 已强制禁用 RGA，使用 CPU 处理图像")

# ========== 子模块配置 ==========
add_subdirectory(lib/rknn/3rdparty)
add_subdirectory(lib/rknn/utils)
add_subdirectory(src)  # src 目录会继承 ROOT_INCLUDE_DIRS