#include "graph/eulerian-trail.hpp"
#include <gtest/gtest.h>

namespace testing {

using eulerian_trail::trail_directed;

TEST(TestEulerianTrail, DirectedExample) {
    {
        int n = 4;
        auto edges = Vec<pair<int, int>>{{0, 1}, {2, 0}, {0, 2}, {3, 0},
                                         {1, 3}, {2, 3}, {3, 3}};
        EXPECT_TRUE(trail_directed(n, edges).has_value());
    }
    {
        int n = 4;
        auto edges =
            Vec<pair<int, int>>{{0, 1}, {2, 0}, {0, 3}, {1, 2}, {3, 1}, {2, 3}};
        EXPECT_FALSE(trail_directed(n, edges).has_value());
    }
    {
        int n = 6;
        auto edges =
            Vec<pair<int, int>>{{0, 3}, {1, 2}, {4, 0}, {5, 1}, {4, 4},
                                {2, 3}, {3, 1}, {3, 2}, {1, 4}, {1, 5}};
        EXPECT_TRUE(trail_directed(n, edges).has_value());
    }
}

}  // namespace testing