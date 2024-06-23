#include <catch2/catch_test_macros.hpp>

#include "contest/base.hpp"
#include "number-theory/factor.hpp"

TEST_CASE("Factorize: primality test", "[factor]") {
	using namespace factor;
	
	constexpr u64 N = 1000000;
	for (u64 n = 2; n < N; n++) {
		REQUIRE(is_prime(n) == [&]() -> bool {
			for (u64 d = 2; d * d <= n; d++) {
				if (n % d == 0) return false;
			}
			return true;
		}());
	}

	REQUIRE(!is_prime(u64(1)));
	REQUIRE(is_prime(u64(9223372036854775783)));
	REQUIRE(!is_prime(u64(7156857700403137441)));
}

TEST_CASE("Factorize", "[factor]") {
	using namespace factor;
	
	REQUIRE(factorize<u64>(997748200186314745) == Vec<u64>{5, 7, 17, 17, 17581, 5610628223});

	const int N = 10000;
	// minimum prime factor
	Vec<int> pfac(N);
	iota(pfac.begin(), pfac.end(), 0);
	for (int a = 2; a*a < N; a++) {
		if (a == pfac[a]) {
			for (int b = a*a; b < N; b += a) {
				if (pfac[b] == b) {
					pfac[b] = a;
				}
			}
		}
	}

	auto factorize_naive = [&](int n) -> Vec<int> {
		Vec<int> res;
		while (n > 1) {
			int p = pfac[n];
			n /= p;
			res.push_back(p);
		}
		return res;
	};
	for (int a = 2; a < N; a++) {
		REQUIRE(factorize<int>(a) == factorize_naive(a));
	}
}

TEST_CASE("Factorize: primitive roots", "[factor]") {
	using namespace factor;

	constexpr int MAX = 2345;
	for (int p = 2; p < MAX; p++) {
		if (!is_prime(p)) continue;

		auto root = primitive_root(p);
		Vec<bool> seen(p);
		int v = 1;
		for (int z = 0; z < p-1; z++) {
			REQUIRE(!seen[v]);
			REQUIRE(v);
			seen[v] = true;
			v = int(i64(v) * root % p);
		}
		REQUIRE(v == 1);
	}
}