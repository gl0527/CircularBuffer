add_executable(CircularBufferTest test.cpp)
set_property(TARGET CircularBufferTest PROPERTY EXPORT_COMPILE_COMMANDS ON)
target_link_libraries(CircularBufferTest PRIVATE gtest_main CircularBuffer)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/gtest" "lib/gtest")

add_test(NAME CircularBufferTest COMMAND CircularBufferTest)
