#include "number-theory/factor.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "contest/base.hpp"

namespace testing {

using namespace factor;

TEST(FactorTest, Primality) {
	constexpr u64 N = 10000;
	for (u64 n = 2; n < N; n++) {
		EXPECT_TRUE(is_prime(n) == [&]() -> bool {
			for (u64 d = 2; d * d <= n; d++) {
				if (n % d == 0) return false;
			}
			return true;
		}());
	}

	EXPECT_FALSE(is_prime(u64(1)));
	EXPECT_TRUE(is_prime(u64(9223372036854775783)));
	EXPECT_FALSE(is_prime(u64(7156857700403137441)));
}

TEST(FactorTest, Factorize) {
	EXPECT_THAT(factorize<u64>(997748200186314745),
				testing::ElementsAre(5, 7, 17, 17, 17581, 5610628223));

	constexpr int N = 10000;
	// minimum prime factor
	auto pfac = Vec<int>(N);
	iota(begin(pfac), end(pfac), 0);
	for (int a = 2; a * a < N; a++) {
		if (a == pfac[a]) {
			for (int b = a * a; b < N; b += a) {
				if (pfac[b] == b) {
					pfac[b] = a;
				}
			}
		}
	}

	auto factorize_naive = [&](int n) -> Vec<int> {
		auto res = Vec<int>();
		while (n > 1) {
			int p = pfac[n];
			n /= p;
			res.push_back(p);
		}
		return res;
	};
	for (int a = 2; a < N; a++) {
		EXPECT_EQ(factorize<int>(a), factorize_naive(a));
	}
}

TEST(FactorTest, PrimitiveRoots) {
	constexpr int MAX = 300;
	for (int p = 2; p < MAX; p++) {
		if (!is_prime(p)) continue;

		auto root = primitive_root(p);
		auto seen = Vec<bool>(p);
		int v = 1;
		for (int z = 0; z < p - 1; z++) {
			EXPECT_FALSE(seen[v]);
			EXPECT_GT(v, 0);
			seen[v] = true;
			v = int(i64(v) * root % p);
		}
		EXPECT_EQ(v, 1);
	}
}

}  // namespace testing