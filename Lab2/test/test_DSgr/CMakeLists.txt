cmake_minimum_required(VERSION 3.12)

project(.)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 查找源文件
file(GLOB SOURCES ../src/*.cpp)


# 启用测试
enable_testing()

# 添加 GoogleTest 子目录
add_subdirectory("../../googletest" "${CMAKE_BINARY_DIR}/googletest")

# 包含头文件目录
include_directories(
        include
        ${CMAKE_SOURCE_DIR}/googletest/googletest/include
)

# 添加测试可执行文件
add_executable(test_DSgr test_DSgr.cpp ${SOURCES})

# 链接 GoogleTest 库
target_link_libraries(test_DSgr gtest gtest_main)