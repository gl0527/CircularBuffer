cmake_minimum_required(VERSION 3.16)
project(CircularBuffer VERSION 1.0.0 LANGUAGES CXX)

include(CTest)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/circular_buffer)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()
