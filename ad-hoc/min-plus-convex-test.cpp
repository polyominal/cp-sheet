#include "ad-hoc/min-plus-convex.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(TestMinPlusConvex, Example) {
	auto a = Vec<i64>{3, 1, 0, 3};
	auto b = Vec<i64>{5, 1, 3, 3, 2};
	EXPECT_THAT(min_plus_convex(a, b),
				testing::ElementsAre(8, 4, 2, 1, 3, 3, 2, 5));
}