#include <gtest/gtest.h>
#include <ad-hoc/palindromic-decomp-dp.hpp>
#include <algebra/modint.hpp>
#include <string/manacher.hpp>
#include <util/random.hpp>

template <class S, bool even = false>
Vec<S> palindromic_decomp_dp_naive(const Vec<u8>& a,
								   auto add,
								   S add_e,
								   auto mul_x,
								   S mul_e) {
	int n = int(a.size());
	assert(n > 0);
	auto man = manacher(n, [&](int i, int j) -> bool { return a[i] == a[j]; });
	auto is_pal = [&](int l, int r) -> bool {
		assert(0 <= l && l < r && r <= n);
		if constexpr (even) {
			if ((r - l) % 2) return false;
		}
		return r - l <= man[l + r];
	};
	Vec<S> dp(n + 1, add_e);
	dp[0] = mul_e;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (is_pal(i, j)) {
				dp[j] = add(dp[j], mul_x(dp[i]));
			}
		}
	}
	return dp;
}

namespace testing {

TEST(TestPalindromicDecompositionDP, ProductOfX) {
	auto rng = Random(20240112);

	const u32 MOD = u32(1e9) + 7;
	using Z = ModInt<MOD>;
	using S = Z;
	const S x = rng.uniform<uint32_t>(1, MOD - 1);
	auto add = [](S a, S b) -> S { return a + b; };
	auto mul_x = [&x](S a) -> S { return a * x; };
	S add_e = 0, mul_e = 1;

	{
		for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
			constexpr int K = 3;
			auto A = Vec<u8>(N);
			for (u8& a : A) a = rng.uniform<u8>(0, K - 1);
			{
				auto res =
					palindromic_decomp_dp<S>(A, add, add_e, mul_x, mul_e);
				auto res_naive =
					palindromic_decomp_dp_naive<S>(A, add, add_e, mul_x, mul_e);
				EXPECT_EQ(res, res_naive);
			}
		}
	}

	for (int N : {2, 4, 6, 8, 34, 100}) {
		constexpr int K = 3;
		auto A = Vec<u8>(N);
		for (u8& a : A) a = rng.uniform<u8>(0, K - 1);
		{
			auto res =
				palindromic_decomp_dp<S, true>(A, add, add_e, mul_x, mul_e);
			auto res_naive = palindromic_decomp_dp_naive<S, true>(A, add, add_e,
																  mul_x, mul_e);
			EXPECT_EQ(res, res_naive);
		}
	}
}

}  // namespace testing