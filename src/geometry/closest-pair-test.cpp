#include "geometry/closest-pair.hpp"
#include <gtest/gtest.h>
#include "contest/base.hpp"

namespace testing {

TEST(ClosestPairTest, Sample) {
    using geometry::closest_pair;
    using geometry::Point;

    using P = Point<i64>;

    {
        auto pts = Vec<P>{
            P(-1, -1), P(-6, 4), P(-9, -7), P(2, 5), P(-7, 6),
        };

        // P[1] and P[4]: 0^2 + 2^2 = 5
        i64 best = 1e18;
        closest_pair(pts, [&](P a, P b) { best = dist2(a - b); });
        EXPECT_EQ(best, 5);
    }
}

}  // namespace testing