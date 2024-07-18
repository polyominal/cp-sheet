#include <contest/base.hpp>
#include <geometry/closest-pair.hpp>
#include <gtest/gtest.h>

TEST(ClosestPairTest, Sample) {
	using P = pair<i64, i64>;

	{
		auto pts = Vec<P>{
			P(-1, -1),
			P(-6, 4),
			P(-9, -7),
			P(2, 5),
			P(-7, 6),
		};

		// P[1] and P[4]: 0^2 + 2^2 = 5
		auto best = closest_pair_impl::closest_pair(pts);
		EXPECT_EQ(get<0>(best), 5);
	}
}