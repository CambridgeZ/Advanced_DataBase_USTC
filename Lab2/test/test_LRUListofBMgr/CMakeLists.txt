cmake_minimum_required(VERSION 3.12)

project(test_LRUListofBMgr)

set(CMAKE_CXX_STANDARD 17)

# 包含测试框架
enable_testing()
add_subdirectory("../../googletest" "${CMAKE_BINARY_DIR}/googletest")

# 设置源文件
file(GLOB SOURCES ../../src/*.cpp)

# 包含头文件
include_directories(
        include
        ${CMAKE_SOURCE_DIR}/googletest/googletest/include
)

# 定义可执行目标
add_executable(test_LRUListofBMgr test_LRUListofBMgr.cpp ${SOURCES})

# 链接测试框架到目标
target_link_libraries(test_LRUListofBMgr PRIVATE gtest gtest_main)