#include "data-structure/fast-set.hpp"
#include "gtest/gtest.h"

namespace testing {

TEST(TestFastSet, Example) {
    constexpr int n = 10;
    auto fs = FastSet(n);
    EXPECT_TRUE(fs.empty());
    EXPECT_EQ(fs.next(0), n);
    EXPECT_EQ(fs.prev(0), -1);

    fs.set(4);
    EXPECT_EQ(fs.next(0), 4);
    EXPECT_EQ(fs.next(3), 4);
    EXPECT_EQ(fs.next(4), 4);
    EXPECT_EQ(fs.next(5), n);
    EXPECT_EQ(fs.prev(4), 4);
    EXPECT_EQ(fs.prev(3), -1);
    EXPECT_EQ(fs.prev(10), 4);

    fs.set(7);
    EXPECT_EQ(fs.next(0), 4);
    EXPECT_EQ(fs.prev(10), 7);
    EXPECT_EQ(fs.next(4), 4);
    EXPECT_EQ(fs.next(5), 7);
    EXPECT_EQ(fs.prev(8), 7);

    fs.reset(4);
    EXPECT_EQ(fs.next(0), 7);
    EXPECT_EQ(fs.prev(10), 7);
    EXPECT_EQ(fs.next(4), 7);
    EXPECT_EQ(fs.next(5), 7);
    EXPECT_EQ(fs.prev(8), 7);
}

}  // namespace testing