#include "graph/scc.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "data-structure/flatten-vector.hpp"

namespace testing {

Vec<Vec<int>> get_scc_comps(int n, const Vec<pair<int, int>>& edges) {
	auto g = FlattenVector<int>(n, edges);
	auto comps = Vec<Vec<int>>();
	get_scc(g, [&](const Vec<int>& comp) { comps.push_back(comp); });
	return comps;
}

TEST(TestSCC, Example) {
	{
		int n = 6;
		auto edges = Vec<pair<int, int>>{{1, 4}, {5, 2}, {3, 0}, {5, 5},
										 {4, 1}, {0, 3}, {4, 2}};
		EXPECT_THAT(get_scc_comps(n, edges),
					UnorderedElementsAre(
						UnorderedElementsAre(5), UnorderedElementsAre(4, 1),
						UnorderedElementsAre(2), UnorderedElementsAre(0, 3)));
	}
}

}  // namespace testing