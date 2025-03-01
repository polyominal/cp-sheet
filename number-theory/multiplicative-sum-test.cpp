#include "number-theory/multiplicative-sum.hpp"
#include <gtest/gtest.h>
#include "algebra/modint.hpp"
#include "number-theory/eratosthenes.hpp"

namespace testing {

using multiplicative_sum::get_totient_sum;

TEST(TestMultiplicativeSum, TestTotientFunction) {
	using Z = ModInt<998244353>;
	auto primes = prime_enumerate(1e6);
	EXPECT_EQ(get_totient_sum<Z>(5, primes), Z(10));
	EXPECT_EQ(get_totient_sum<Z>(6, primes), Z(12));
	EXPECT_EQ(get_totient_sum<Z>(8, primes), Z(22));
}

}  // namespace testing