#include "data-structure/hash-map.hpp"
#include <gtest/gtest.h>

namespace testing {

TEST(TestHashMap, TestUnsigned64) {
    auto hm = HashMap<u64, u64>();
    EXPECT_TRUE(hm.find(4) == end(hm));
    hm[4] = 233;
    EXPECT_EQ(hm[4], 233);
    hm.erase(4);
    EXPECT_TRUE(hm.find(4) == end(hm));
    EXPECT_EQ(hm[4], 0);
}

}  // namespace testing