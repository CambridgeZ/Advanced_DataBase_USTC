cmake_minimum_required(VERSION 3.12)

project(test_BMgr)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES ../../src/*.cpp)

enable_testing()

add_subdirectory("../../googletest" "${CMAKE_BINARY_DIR}/googletest")

include_directories(
        include
        ${CMAKE_SOURCE_DIR}/googletest/googletest/include
)

add_executable(test_BMgr test_BMgr.cpp ${SOURCES})

target_link_libraries(test_BMgr gtest gtest_main)

