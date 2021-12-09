find_package(GTest REQUIRED)

add_executable(CircularBufferTest test.cpp)
target_include_directories(CircularBufferTest PRIVATE ${PROJECT_SOURCE_DIR}/include ${GTEST_INCLUDE_DIRS})
target_link_libraries(CircularBufferTest PRIVATE ${GTEST_LIBRARIES} pthread)

add_test(NAME CircularBufferTest COMMAND CircularBufferTest)
