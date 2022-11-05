#include "circular_buffer/circular_buffer.hpp"

#include <gtest/gtest.h>
#include <string>

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

TEST(CircularBufferTest, PerformanceTestOnBigObject) {
    constexpr uint64_t limit{300'000'000};
    constexpr std::size_t capacity{16};

    struct BigObject {
        char arr[1024];

        BigObject() = default;

        BigObject(BigObject const &) = delete;
        BigObject &operator=(BigObject const &) = delete;

        BigObject(BigObject &&) = default;
        BigObject &operator=(BigObject &&) = default;
    };

    CircularBuffer<BigObject, capacity> cb;

    for (uint64_t i = 0; i < limit; ++i) {
        cb.push(BigObject{});
    }
    for (std::size_t i = 0; i < capacity; ++i) {
        EXPECT_NO_THROW(cb.pop());
    }
}

TEST(CircularBufferTest, RuleOfFiveTest) {
    // ctor
    CircularBuffer<std::string, 4> buf1;

    buf1.push("apple");
    buf1.push("pear");
    buf1.push("plum");
    buf1.push("peach");

    // copy ctor
    auto buf2 = buf1;

    EXPECT_STREQ("apple", buf2.pop().c_str());
    EXPECT_STREQ("pear", buf2.pop().c_str());
    EXPECT_STREQ("plum", buf2.pop().c_str());
    EXPECT_STREQ("peach", buf2.pop().c_str());

    // ref
    auto &buf3 = buf1;
    // copy ctor
    auto buf4 = buf2;
    // copy assignment
    buf4 = buf3;

    EXPECT_STREQ("apple", buf4.pop().c_str());
    EXPECT_STREQ("pear", buf4.pop().c_str());
    EXPECT_STREQ("plum", buf4.pop().c_str());
    EXPECT_STREQ("peach", buf4.pop().c_str());

    buf2.push("car");
    buf2.push("bike");
    buf2.push("truck");
    buf2.push("bicycle");

    // move ctor
    auto buf5 = std::move(buf2);

    EXPECT_STREQ("car", buf5.pop().c_str());
    EXPECT_STREQ("bike", buf5.pop().c_str());
    EXPECT_STREQ("truck", buf5.pop().c_str());
    EXPECT_STREQ("bicycle", buf5.pop().c_str());

    EXPECT_STRNE("car", buf2.pop().c_str());
    EXPECT_STRNE("bike", buf2.pop().c_str());
    EXPECT_STRNE("truck", buf2.pop().c_str());
    EXPECT_STRNE("bicycle", buf2.pop().c_str());

    buf5.push("triangle");
    buf5.push("rectangle");
    buf5.push("square");
    buf5.push("sphere");

    // move assignment
    buf4 = std::move(buf5);

    EXPECT_STREQ("triangle", buf4.pop().c_str());
    EXPECT_STREQ("rectangle", buf4.pop().c_str());
    EXPECT_STREQ("square", buf4.pop().c_str());
    EXPECT_STREQ("sphere", buf4.pop().c_str());

    EXPECT_STRNE("triangle", buf5.pop().c_str());
    EXPECT_STRNE("rectangle", buf5.pop().c_str());
    EXPECT_STRNE("square", buf5.pop().c_str());
    EXPECT_STRNE("sphere", buf5.pop().c_str());
}

TEST(CircularBufferTest, LeftShiftOperatorTest) {
    CircularBuffer<int, 8> cb;

    cb << 6 << 2 << 5 << 19 << 0 << -7;

    EXPECT_EQ(6, cb.pop());
    EXPECT_EQ(2, cb.pop());
    EXPECT_EQ(5, cb.pop());
    EXPECT_EQ(19, cb.pop());
    EXPECT_EQ(0, cb.pop());
    EXPECT_EQ(-7, cb.pop());

    cb.reset();

    int a{ 101 }, b{ 42 };

    cb << 9 << 2 << 16 << 22 << -3 << 1 << a << 7 << b;
    cb << b << 0 << a;

    EXPECT_EQ(-3, cb.pop());
    EXPECT_EQ(1, cb.pop());
    EXPECT_EQ(a, cb.pop());
    EXPECT_EQ(7, cb.pop());
    EXPECT_EQ(b, cb.pop());
    EXPECT_EQ(b, cb.pop());
    EXPECT_EQ(0, cb.pop());
    EXPECT_EQ(a, cb.pop());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
