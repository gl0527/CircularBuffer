add_executable(CircularBufferTest test.cpp)
target_link_libraries(CircularBufferTest PRIVATE gtest_main pthread CircularBuffer)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/gtest" "lib/gtest")

add_test(NAME CircularBufferTest COMMAND CircularBufferTest)
