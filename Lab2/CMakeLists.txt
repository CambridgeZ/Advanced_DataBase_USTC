cmake_minimum_required(VERSION 3.12)

# 定义项目名称
project(test_buffer_manager)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置默认的构建类型为 Debug（如未通过命令行指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/../include)

# 查找 src 文件夹中的所有 .cpp 文件并添加到 SOURCE_FILES
file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# 添加可执行文件
add_executable(test_buffer_manager main.cpp ${SOURCE_FILES})

# 强制添加调试符号
target_compile_options(test_buffer_manager PRIVATE $<$<CONFIG:Debug>:-g>)

# 显示编译信息和警告（可选，开发阶段推荐开启）
target_compile_options(test_buffer_manager PRIVATE -Wall -Wextra -Wpedantic)