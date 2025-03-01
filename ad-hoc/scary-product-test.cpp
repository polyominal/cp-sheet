#include "ad-hoc/scary-product.hpp"
#include <gtest/gtest.h>
#include "util/random.hpp"

namespace testing {

i64 sum_of_floor_of_linear(i64 n, i64 m, i64 a, i64 b) {
	i64 sum = 0;
	for (i64 i = 0; i < n; i++) {
		sum += (a * i + b) / m;
	}
	return sum;
}

TEST(TestScaryProduct, SumOfFloorOfLinear) {
	auto rng = Random(20240914);
	for (int case_num = 0; case_num < 50; case_num++) {
		i64 n = rng.uniform<i64>(1, i64(2e4));
		i64 m = rng.uniform<i64>(1, i64(1e9));
		i64 a = rng.uniform<i64>(0, m - 1);
		i64 b = rng.uniform<i64>(0, m - 1);
		i64 sum = scary_prod(n, a, b, m, Sum(), Sum(1, 0, 0), Sum(0, 1, 0)).res;
		i64 sum_expected = sum_of_floor_of_linear(n, m, a, b);
		EXPECT_EQ(sum, sum_expected);
	}
}

i64 min_of_mod_of_linear(i64 n, i64 m, i64 a, i64 b) {
	i64 min_mod = 1e18;
	for (i64 i = 0; i < n; i++) {
		min_mod = std::min(min_mod, (a * i + b) % m);
	}
	return min_mod;
}

TEST(TestScaryProduct, MinOfModOfLinear) {
	auto rng = Random(20240914);
	for (int case_num = 0; case_num < 50; case_num++) {
		i64 n = rng.uniform<i64>(1, i64(2e4));
		i64 m = rng.uniform<i64>(1, i64(1e9));
		i64 a = rng.uniform<i64>(0, m - 1);
		i64 b = rng.uniform<i64>(0, m - 1);
		i64 min_mod = b + scary_prod(n, a, b, m, MinMod(), MinMod(a, 0),
									 MinMod(-m, MinMod::INF))
							  .best;
		i64 min_mod_expected = min_of_mod_of_linear(n, m, a, b);
		EXPECT_EQ(min_mod, min_mod_expected);
	}
}

}  // namespace testing