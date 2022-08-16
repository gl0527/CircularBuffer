cmake_minimum_required(VERSION 3.20)
project(CircularBuffer LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(${PROJECT_NAME} INTERFACE "/W4" "/WX" "$<$<CONFIG:RELEASE>:/O2>")
else()
    target_compile_options(${PROJECT_NAME} INTERFACE "-Wall" "-Wextra" "-Werror" "-pedantic" "-Winit-self" "-Wuninitialized" "-Woverloaded-virtual" "-Wshadow" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} INTERFACE "-stdlib=libc++")
    else()
        # nothing to add
    endif()
endif()

target_include_directories(${PROJECT_NAME} INTERFACE include/)

option(BUILD_TESTS "Build unit tests." ON)

if (BUILD_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()
