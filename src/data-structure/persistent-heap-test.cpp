#include "data-structure/persistent-heap.hpp"
#include <gtest/gtest.h>

namespace testing {

TEST(TestMeldableHeap, Example) {
    auto hm = HeapManager<int>();
    auto a = hm.make_empty();
    EXPECT_FALSE(hm.top(a).has_value());

    auto b = hm.make_single(1);
    EXPECT_EQ(hm.top(b).value(), 1);
    b = hm.meld(a, b);
    EXPECT_EQ(hm.top(b).value(), 1);

    auto c = hm.push(b, 0);
    EXPECT_EQ(hm.top(c).value(), 0);
    EXPECT_EQ(hm.top(b), 1);

    auto d = hm.meld(b, c);
    EXPECT_EQ(hm.top(d).value(), 0);
    EXPECT_EQ(hm.top(b).value(), 1);
}

}  // namespace testing