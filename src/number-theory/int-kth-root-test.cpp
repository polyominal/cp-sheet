#include <contest/base.hpp>
#include <number-theory/int-kth-root.hpp>

#include <gtest/gtest.h>

TEST(IntKthRootTest, LibraryCheckerExample) {
	auto f = [&](u64 a, u64 k) -> u64 { return int_kth_root(a, k); };

	EXPECT_EQ(f(215, 3), 5);
	EXPECT_EQ(f(216, 3), 6);
	EXPECT_EQ(f(217, 3), 6);

	EXPECT_EQ(f(9999999999ull, 10), 9);
	EXPECT_EQ(f(10000000000ull, 10), 10);
	EXPECT_EQ(f(10000000001ull, 10), 10);

	EXPECT_EQ(f(18446744073709551615ull, 1), 18446744073709551615ull);
	EXPECT_EQ(f(18446744073709551615ull, 2), 4294967295ull);
	EXPECT_EQ(f(18446744073709551615ull, 63), 2ull);
	EXPECT_EQ(f(18446744073709551615ull, 64), 1ull);
}