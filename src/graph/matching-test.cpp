#include "graph/matching.hpp"
#include <gtest/gtest.h>

namespace testing {

TEST(TestMatching, Example) {
    auto mm = MaxMatching(7);
    auto edges = Vec<pair<int, int>>{{2, 0}, {0, 5}, {5, 6}, {6, 1},
                                     {1, 0}, {1, 3}, {3, 4}, {1, 4}};
    for (auto [a, b] : edges) {
        mm.add_edge(a, b);
    }
    EXPECT_EQ(mm.max_matching().size(), 3);
}

}  // namespace testing