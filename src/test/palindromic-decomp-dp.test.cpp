#include <catch2/catch_test_macros.hpp>

#include "ad-hoc/palindromic-decomp-dp.hpp"
#include "string/manacher.hpp"
#include "util/random.hpp"
#include "algebra/modint.hpp"

template <class S, int K, bool even = false>
Vec<S> palindromic_decomp_dp_naive(const Vec<int>& a,
	function<S(S, S)> add, S add_e,
	function<S(S)> mul_x, S mul_e) {
	int n = int(a.size());
	assert(n > 0);
	auto man = manacher(n, [&](int i, int j) -> bool {
		return a[i] == a[j];
	});
	auto is_pal = [&](int l, int r) -> bool {
		assert(0 <= l && l < r && r <= n);
		if constexpr (even) {
			if ((r-l) % 2) return false;
		}
		return r-l <= man[l+r];
	};
	Vec<S> dp(n+1, add_e);
	dp[0] = mul_e;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j <= n; j++) {
			if (is_pal(i, j)) {
				dp[j] = add(dp[j], mul_x(dp[i]));
			}
		}
	}
	return dp;
}

TEST_CASE("Palindromic decomposition DP", "[palindromic-decomp-dp][manacher]") {
	auto rng = Random(20240112);

	const uint32_t mod = int(1e9) + 7;
	using num = ModInt<mod>;
	using S = num;
	const S x = rng.uniform<uint32_t>(1, mod-1);
	auto add = [](S a, S b) -> S { return a + b; };
	auto mul_x = [&x](S a) -> S { return a * x; };
	S add_e = 0, mul_e = 1;

	{
		for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {

			Vec<int> A(N);
			constexpr int K = 3;
			for (int& a : A) a = rng.uniform(0, K-1);
			{
				auto res = palindromic_decomp_dp<S, K>(
					A, add, add_e, mul_x, mul_e
				);
				auto res_naive = palindromic_decomp_dp_naive<S, K>(
					A, add, add_e, mul_x, mul_e
				);
				REQUIRE(res == res_naive);
			}
		}
	}

	for (int N : {2, 4, 6, 8, 34, 100}) {
		Vec<int> A(N);
		constexpr int K = 3;
		for (int& a : A) a = rng.uniform(0, K-1);
		{
			auto res = palindromic_decomp_dp<S, K, true>(
				A, add, add_e, mul_x, mul_e
			);
			auto res_naive = palindromic_decomp_dp_naive<S, K, true>(
				A, add, add_e, mul_x, mul_e
			);
			REQUIRE(res == res_naive);
		}
	}
}