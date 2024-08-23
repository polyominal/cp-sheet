#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tree/cartesian-tree.hpp>

namespace testing {

TEST(TestCartesianTree, Example) {
	auto A = Vec<int>{9, 3, 7, 1, 8, 12, 10, 20, 15, 18, 5};
	auto ct = CartesianTree(A);
	EXPECT_THAT(ct.p, ElementsAre(1, 3, 1, -1, 10, 6, 4, 8, 6, 8, 3));
}

}  // namespace testing