#include "circular_buffer/circular_buffer.hpp"

#include <gtest/gtest.h>

using namespace lg;

TEST(CircularBufferTest, PushTest) {
    CircularBuffer<float, 4> cb;
    cb.push(1);
    cb.push(2.0f, true);
    cb.push(88, false);
    cb.push(-3.2f, false);
    cb.push(-0.2f, false);
    cb.push(-0.3f, true);
    EXPECT_FLOAT_EQ(2.0f, cb.pop());
    EXPECT_FLOAT_EQ(88.0f, cb.pop());
    EXPECT_FLOAT_EQ(-3.2f, cb.pop());
    EXPECT_FLOAT_EQ(-0.3f, cb.pop());
}

TEST(CircularBufferTest, PopTest) {
    CircularBuffer<int, 3> cb;
    EXPECT_DEATH(cb.pop(), "");
    cb.push(1);
    int e = cb.pop();
    EXPECT_EQ(1, e);
    cb.push(0);
    cb.push(1);
    cb.push(2);
    cb.push(3);
    cb.push(4);
    EXPECT_EQ(2, cb.pop());
    EXPECT_EQ(3, cb.pop());
    EXPECT_EQ(4, cb.pop());
}

TEST(CircularBufferTest, ResetTest) {
    CircularBuffer<int, 4> cb;
    cb.push(2);
    cb.push(4);
    cb.push(-9);
    cb.reset();
    EXPECT_TRUE(cb.empty());
    cb.push(1);
    EXPECT_EQ(1, cb.pop());
    EXPECT_DEATH(cb.pop(), "");
}

TEST(CircularBufferTest, SizeTest) {
    CircularBuffer<int, 3> cb;
    EXPECT_EQ(0, cb.size());
    cb.push(11);
    EXPECT_EQ(1, cb.size());
    cb.push(9);
    EXPECT_EQ(2, cb.size());
    cb.push(10);
    EXPECT_EQ(3, cb.size());
    cb.push(1);
    EXPECT_EQ(3, cb.size());
    cb.pop();
    EXPECT_EQ(2, cb.size());
}

TEST(CircularBufferTest, CapacityTest) {
    constexpr CircularBuffer<short, 2> cb;
    EXPECT_EQ(2, cb.capacity());
}

TEST(CircularBufferTest, EmptyTest) {
    CircularBuffer<int, 2> cb;
    EXPECT_TRUE(cb.empty());
    cb.push(1);
    EXPECT_FALSE(cb.empty());
    cb.pop();
    EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, FullTest) {
    CircularBuffer<char, 3> cb;
    EXPECT_FALSE(cb.full());
    cb.push('a');
    EXPECT_FALSE(cb.full());
    cb.push('b');
    EXPECT_FALSE(cb.full());
    cb.push('c');
    EXPECT_TRUE(cb.full());
    cb.pop();
    EXPECT_FALSE(cb.full());
    cb.push('d');
    EXPECT_TRUE(cb.full());
    cb.push('e');
    EXPECT_TRUE(cb.full());
}

TEST(CircularBufferTest, PerformanceTest) {
    constexpr uint64_t limit{3'000'000'000};
    constexpr std::size_t capacity{32};

    CircularBuffer<int, capacity> cb;

    for (uint64_t i = 0; i < limit; ++i) {
        cb.push(2);
    }
    for (std::size_t i = 0; i < capacity; ++i) {
        EXPECT_EQ(2, cb.pop());
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
