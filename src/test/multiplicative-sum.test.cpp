#include <catch2/catch_test_macros.hpp>

#include "number-theory/eratosthenes.hpp"
#include "number-theory/multiplicative-sum.hpp"

TEST_CASE("Multiplicative sum helper: counting primes", "[eratosthenes][multiplicative-sum]") {
	auto all_ps = prime_enumerate(1234567);

	for (int N : {5, 19, 168, 1234567}) {
		auto ps = prime_enumerate(N);
		auto cp = multiplicative_sum::counting_primes<i64, 1>(N, all_ps);
		REQUIRE(int(ps.size()) == int(cp.sum[0][0]));
	}

	{
		auto cp = multiplicative_sum::counting_primes<i64, 1>(i64(1e11), all_ps);
		// Reference:
		// https://www.wolframalpha.com/input?i=number+of+primes+not+greater+than+10%5E11
		REQUIRE(cp.sum[0][0] == i64(4'118'054'813));
	}
}