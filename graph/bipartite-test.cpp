#include "graph/bipartite.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace testing {

TEST(TestBipartite, MatchingExample) {
    auto bip = Bipartite(3, 3);
    bip.add_edge(0, 1);
    bip.add_edge(1, 2);
    bip.add_edge(2, 0);
    bip.run();

    EXPECT_THAT(bip.mtl, ElementsAre(1, 2, 0));
    EXPECT_THAT(bip.matching(),
                UnorderedElementsAre(Pair(0, 1), Pair(1, 2), Pair(2, 0)));
}

}  // namespace testing