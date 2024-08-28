#include "string/eertree.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace testing {

TEST(TestEertree, Example) {
	{
		auto et = Eertree();
		auto s = string("abaccaba");
		// auto lens = Vec<int>();
		auto locs = Vec<int>();
		for (char x : s) {
			locs.push_back(et.append(u8(x)));
		}

		auto lens = Vec<int>();
		for (int v : locs) {
			lens.push_back(et[v].len());
		}
		EXPECT_THAT(lens, ElementsAre(1, 1, 3, 1, 2, 4, 6, 8));

		auto ranges = Vec<pair<int, int>>();
		for (int v : locs) {
			ranges.emplace_back(et[v].l, et[v].r);
		}
		EXPECT_THAT(ranges, ElementsAre(Pair(0, 1), Pair(1, 2), Pair(0, 3),
										Pair(3, 4), Pair(3, 5), Pair(2, 6),
										Pair(1, 7), Pair(0, 8)));

		// EVEN vertex
		EXPECT_EQ(et[0].len(), 0);
		// ODD vertex
		EXPECT_EQ(et[1].len(), -1);
	}
}

}  // namespace testing