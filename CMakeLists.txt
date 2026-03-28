cmake_minimum_required(VERSION 3.10)
project(HikSdkDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_SOC "rk3588" CACHE STRING "Target SOC for RKNN")
set(CMAKE_SYSTEM_NAME "Linux" CACHE STRING "Target system")



# 全局宏定义（替代 add_definitions，更现代）
add_compile_definitions(DISABLE_RGA)
message(STATUS "⚠️ 已强制禁用 RGA，使用 CPU 处理图像")


add_subdirectory(lib/rknn/3rdparty)
add_subdirectory(lib/rknn/utils)
add_subdirectory(src)  # src 会自动继承顶层的变量s