#include "algebra/barrett.hpp"
#include <gtest/gtest.h>
#include "util/random.hpp"

TEST(TestBarrettReduction, RandomOperations) {
	auto rng = Random(20240213);

	EXPECT_EQ(Barrett(10).reduce(0), 0);

	constexpr int Q = 200;
	for (int q = 0; q < Q; q++) {
		u32 a = rng.uniform<u32>(0, (u32(1) << 31) - 1);
		u32 b = rng.uniform<u32>(0, (u32(1) << 31) - 1);
		u32 m = rng.uniform<u32>(0, (u32(1) << 31) - 1);

		u32 res_barrett = Barrett(m).reduce(u64(a) * b);
		u32 res_naive = u32(u64(a) * b % m);
		EXPECT_EQ(res_barrett, res_naive);
	}
	for (int q = 0; q < Q; q++) {
		u64 a = rng.uniform<u64>(0, (u64(1) << 62) - 1);
		u32 m = rng.uniform<u32>(0, (u32(1) << 31) - 1);

		u32 res_barret = Barrett(m).reduce(a);
		u32 res_naive = u32(a % m);
		EXPECT_EQ(res_barret, res_naive);
	}
}