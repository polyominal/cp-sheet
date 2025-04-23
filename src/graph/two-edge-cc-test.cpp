#include "graph/two-edge-cc.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "data-structure/flatten-vector.hpp"

namespace testing {

template <class G>
Vec<Vec<int>> get_2cc_groups(const G& g) {
    auto groups = Vec<Vec<int>>();
    two_edge_cc(g, [&](int t, int v) -> void {
        if (t >= int(groups.size())) {
            groups.resize(t + 1);
        }
        groups[t].push_back(v);
    });
    for (const auto& group : groups) {
        assert(!group.empty());
    }
    return groups;
}

Vec<Vec<int>> get_2cc_groups(int n, Vec<pair<int, int>> edges) {
    // for each (v, w) in edges, add (w, v) to edges
    size_t m = edges.size();
    for (size_t z = 0; z < m; z++) {
        auto [v, w] = edges[z];
        edges.emplace_back(w, v);
    }
    auto g = FlattenVector<int>(n, edges);
    return get_2cc_groups(g);
}

TEST(TestTwoEdgeConnectedComponents, Example) {
    {
        int n = 4;
        auto edges =
            Vec<pair<int, int>>{{0, 2}, {0, 1}, {3, 0}, {2, 1}, {2, 3}};
        auto groups = get_2cc_groups(n, edges);
        EXPECT_THAT(groups,
                    UnorderedElementsAre(UnorderedElementsAre(0, 1, 2, 3)));
    }
    {
        int n = 13;
        auto edges = Vec<pair<int, int>>{
            {4, 5},  {8, 7},   {12, 3}, {3, 10}, {1, 5}, {10, 2}, {0, 0},
            {11, 4}, {2, 12},  {9, 1},  {9, 0},  {7, 8}, {7, 6},  {9, 1},
            {8, 2},  {12, 10}, {11, 0}, {8, 6},  {3, 2}, {5, 9},  {4, 11}};
        auto groups = get_2cc_groups(n, edges);
        EXPECT_THAT(groups, UnorderedElementsAre(
                                UnorderedElementsAre(0, 9, 1, 5, 4, 11),
                                UnorderedElementsAre(2, 10, 3, 12),
                                UnorderedElementsAre(6, 7, 8)));
    }
}

}  // namespace testing