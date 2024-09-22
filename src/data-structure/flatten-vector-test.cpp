#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <data-structure/flatten-vector.hpp>

namespace testing {

TEST(TestFlattenVector, Example) {
	// Copied from
	// <https://github.com/yosupo06/yosupo-library/blob/15046ee7dafa1ba60174fd37b5c03ee9cbe444bf/test/unittest/flattenvector_test.cpp>
	auto fv = FlattenVector<int>(
		3, Vec<pair<int, int>>{{0, 1}, {0, 2}, {1, 10}, {2, 20}, {1, 11}});
	EXPECT_THAT(fv.off, testing::ElementsAre(0, 2, 4, 5));
	EXPECT_THAT(fv.v, testing::ElementsAre(1, 2, 10, 11, 20));
}

}  // namespace testing