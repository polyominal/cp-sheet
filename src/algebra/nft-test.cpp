#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algebra/modint.hpp>
#include <algebra/nft.hpp>
#include <util/random.hpp>

namespace testing {

TEST(TestNFT, MultiplySmall) {
	using Z = ModInt<998244353>;
	auto a = Vec<Z>{1, 2};
	auto b = Vec<Z>{1, 2, 1};
	auto c = multiply(a, b);
	EXPECT_THAT(c, ElementsAre(1, 4, 5, 2));
}

TEST(TestNFT, Multiply) {
	auto rng = Random(20240824);

	using Z = ModInt<998244353>;
	constexpr int N = 1234;
	auto a = Vec<Z>(N);
	for (auto& v : a) {
		v = rng.uniform<u32>(0, Z::get_mod() - 1);
	}
	auto b = Vec<Z>(N);
	for (auto& v : b) {
		v = rng.uniform<u32>(0, Z::get_mod() - 1);
	}

	auto c = Vec<Z>(N + N - 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			c[i + j] += a[i] * b[j];
		}
	}
	EXPECT_EQ(multiply(a, b), c);
}

}  // namespace testing