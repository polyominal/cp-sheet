#include "data-structure/unionfind.hpp"
#include <gtest/gtest.h>

namespace testing {

TEST(TestUnionFind, Example) {
	auto uf = UnionFind(5);
	EXPECT_TRUE(uf.same(0, 0));
	EXPECT_FALSE(uf.unite(0, 0).has_value());
	EXPECT_TRUE(uf.unite(0, 1).has_value());
	EXPECT_TRUE(uf.unite(1, 2).has_value());
	EXPECT_TRUE(uf.same(0, 2));
	EXPECT_FALSE(uf.unite(0, 2).has_value());
	EXPECT_TRUE(uf.unite(0, 4).has_value());
	EXPECT_FALSE(uf.same(0, 3));
	EXPECT_TRUE(uf.unite(3, 4).has_value());
	EXPECT_TRUE(uf.same(0, 3));
}

}  // namespace testing