cmake_minimum_required(VERSION 3.7)
project(CircularBuffer VERSION 1.2.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -W -Wall -Wextra -Winit-self -Wuninitialized -Woverloaded-virtual -Wshadow")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/circular_buffer)

if (BUILD_TESTING)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()
