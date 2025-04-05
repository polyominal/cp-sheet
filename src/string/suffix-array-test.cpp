#include "string/suffix-array.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "contest/base.hpp"

namespace testing {

TEST(SuffixArrayTest, Sample) {
    {
        auto sa = SuffixArray::construct(string("abcbcba"));
        EXPECT_THAT(sa.sa, ElementsAre(6, 0, 5, 3, 1, 4, 2));
        EXPECT_THAT(sa.lcp, ElementsAre(1, 0, 1, 3, 0, 2));
    }
}

}  // namespace testing