#include "graph/complement-graph.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace testing {

Vec<Vec<int>> get_cc(const ComplementGraph& cg) {
	Vec<Vec<int>> comps;
	cg.get_connected([&](const Vec<int>& comp) { comps.push_back(comp); });
	return comps;
}

TEST(TestComplementGraph, ConnectedComponentsExample) {
	auto cg = ComplementGraph(5);
	// no edges -> a complete graph
	EXPECT_THAT(get_cc(cg),
				UnorderedElementsAre(UnorderedElementsAre(0, 1, 2, 3, 4)));

	// All edges between {0, 1, 2} and {3, 4} -> {0, 1, 2}, {3, 4}
	for (int x : {0, 1, 2}) {
		for (int y : {3, 4}) {
			cg.add_edge(x, y);
		}
	}
	EXPECT_THAT(get_cc(cg), UnorderedElementsAre(UnorderedElementsAre(0, 1, 2),
												 UnorderedElementsAre(3, 4)));
}

}  // namespace testing