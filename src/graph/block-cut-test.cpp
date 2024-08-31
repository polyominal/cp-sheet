#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <data-structure/flatten-vector.hpp>
#include <graph/block-cut.hpp>

namespace testing {

template <class G> Vec<Vec<int>> get_bct_groups(const G& g) {
	auto groups = Vec<Vec<int>>();
	block_cut_tree(g, [&](int t, int v) -> void {
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

Vec<Vec<int>> get_bct_groups(int n, Vec<pair<int, int>> edges) {
	// for each (v, w) in edges, add (w, v) to edges
	size_t m = edges.size();
	for (size_t z = 0; z < m; z++) {
		auto [v, w] = edges[z];
		edges.emplace_back(w, v);
	}
	auto g = FlattenVector<int>(n, edges);
	return get_bct_groups(g);
}

TEST(TestBlockCutTree, Example) {
	{
		int n = 3;
		auto edges = Vec<pair<int, int>>{{0, 1}, {0, 2}};
		auto groups = get_bct_groups(n, edges);
		EXPECT_THAT(groups, UnorderedElementsAre(UnorderedElementsAre(0, 1),
												 UnorderedElementsAre(0, 2)));
	}
	{
		int n = 3;
		auto edges = Vec<pair<int, int>>{{0, 1}, {0, 2}, {1, 2}};
		auto groups = get_bct_groups(n, edges);
		EXPECT_THAT(groups,
					UnorderedElementsAre(UnorderedElementsAre(0, 1, 2)));
	}
	{
		int n = 10;
		auto edges = Vec<pair<int, int>>{
			{0, 6}, {0, 8}, {1, 2}, {1, 6}, {2, 6}, {3, 6},
			{3, 9}, {4, 9}, {4, 7}, {5, 6}, {5, 9}, {6, 8},
		};
		auto groups = get_bct_groups(n, edges);
		EXPECT_THAT(groups,
					UnorderedElementsAre(UnorderedElementsAre(0, 6, 8),
										 UnorderedElementsAre(1, 2, 6),
										 UnorderedElementsAre(3, 5, 6, 9),
										 UnorderedElementsAre(4, 7),
										 UnorderedElementsAre(4, 9)));
	}
}

}  // namespace testing