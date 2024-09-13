#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <data-structure/flatten-vector.hpp>
#include <graph/dominator.hpp>

namespace testing {

TEST(TestDominator, Example) {
	{
		constexpr int n = 5;
		auto edges =
			Vec<pair<int, int>>{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {0, 3}, {2, 4}};
		auto idom = build_idom(n, FlattenVector<int>(n, edges), 0);
		EXPECT_THAT(idom, ElementsAre(-1, 0, 1, 0, 0));
	}
	{
		constexpr int n = 8;
		auto edges = Vec<pair<int, int>>{{4, 2}, {4, 3}, {2, 0}, {3, 0},
										 {0, 1}, {3, 5}, {3, 6}, {7, 6}};
		auto g = FlattenVector<int>(8, edges);
		auto idom = build_idom(n, g, 4);
		EXPECT_THAT(idom, ElementsAre(4, 0, 4, 4, -1, 3, 3, -1));
	}
}

}  // namespace testing