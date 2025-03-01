#include "graph/mst-kruskal.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace testing {

template <class T>
using E = kruskal_impl::E<T>;
using kruskal_impl::mst;

TEST(TestMSTKruskal, Simple) {
    int n = 4;
    std::vector<E<int>> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {3, 0, 4}};
    auto result = Vec<int>();
    mst(n, edges, [&](int i) { result.push_back(i); });
    EXPECT_THAT(result, ElementsAre(0, 1, 2));
}

}  // namespace testing