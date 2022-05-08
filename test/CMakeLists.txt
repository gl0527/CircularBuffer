add_executable(CircularBufferTest test.cpp)
target_include_directories(CircularBufferTest PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(CircularBufferTest PRIVATE gtest_main pthread)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/gtest" "lib/gtest")

add_test(NAME CircularBufferTest COMMAND CircularBufferTest)
