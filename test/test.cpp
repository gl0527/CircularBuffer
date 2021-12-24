#include "circular_buffer/circular_buffer.hpp"

#include <gtest/gtest.h>

TEST(CircularBufferTest, PushTest) {
    CircularBuffer<float, 4> cb;
    cb.push(1);
    cb.push(2.0f, true);
    cb.push(88, false);
    cb.push(-3.2f, false);
    cb.push(-0.2f, false);
    cb.push(-0.3f, true);
    EXPECT_FLOAT_EQ(cb.pop(), 2.0f);
    EXPECT_FLOAT_EQ(cb.pop(), 88.0f);
    EXPECT_FLOAT_EQ(cb.pop(), -3.2f);
    EXPECT_FLOAT_EQ(cb.pop(), -0.3f);
}

TEST(CircularBufferTest, PopTest) {
    CircularBuffer<int, 3> cb;
    EXPECT_DEATH(cb.pop(), "");
    cb.push(1);
    int e = cb.pop();
    EXPECT_EQ(e, 1);
    cb.push(0);
    cb.push(1);
    cb.push(2);
    cb.push(3);
    cb.push(4);
    EXPECT_EQ(cb.pop(), 2);
    EXPECT_EQ(cb.pop(), 3);
    EXPECT_EQ(cb.pop(), 4);
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
    EXPECT_EQ(cb.size(), 0);
    cb.push(11);
    EXPECT_EQ(cb.size(), 1);
    cb.push(9);
    EXPECT_EQ(cb.size(), 2);
    cb.push(10);
    EXPECT_EQ(cb.size(), 3);
    cb.push(1);
    EXPECT_EQ(cb.size(), 3);
    cb.pop();
    EXPECT_EQ(cb.size(), 2);
}

TEST(CircularBufferTest, CapacityTest) {
    constexpr CircularBuffer<short, 2> cb;
    EXPECT_EQ(cb.capacity(), 2);
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
