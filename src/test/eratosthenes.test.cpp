#include <catch2/catch_test_macros.hpp>

#include "number-theory/eratosthenes.hpp"
#include "util/random.hpp"

TEST_CASE("Eratosthenes sieve: enumerating primes", "[eratosthenes]") {
	constexpr int MAXN = 1e6;
	V<bool> not_prime(MAXN);
	for (int a = 2; a * a < MAXN; a++) {
		if (not_prime[a]) continue;
		for (int b = a * a; b < MAXN; b += a) {
			not_prime[b] = true;
		}
	}
	V<int> primes;
	for (int a = 2; a < MAXN; a++) {
		if (!not_prime[a]) primes.push_back(a);
	}

	V<int> pref;
	auto verify_given_N = [&](int N) -> void {
		pref.clear();
		for (int p : primes) {
			if (p <= N) {
				pref.push_back(p);
			} else {
				break;
			}
		}
		REQUIRE(pref == prime_enumerate(N));
	};
	
	auto rng = Random(20240111);
	for (int z = 0; z < 5; z++) {
		int N = rng.uniform(1, MAXN-1);
		verify_given_N(N);
	}
	// use prime bounds
	for (int z = 0; z < 5; z++) {
		int prime_idx = rng.uniform(0, int(primes.size()) - 1);
		int N = primes[prime_idx];
		verify_given_N(N);
	}
}