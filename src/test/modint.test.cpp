#include <catch2/catch_test_macros.hpp>

#include "algebra/modint.hpp"
#include "util/random.hpp"

TEST_CASE("Modint: multiplication/inversion", "[modint]") {
	auto rng = Random(114514);

	constexpr uint32_t mod = 998244353;
	using num = modint<mod>;

	for (int z = 0; z < 200; z++) {
		num a = rng.uniform<uint32_t>(1, mod-1);
		num ia = num(1) / a;
		num ia2 = inv(a);
		REQUIRE(ia == ia2);
		REQUIRE((a * ia) == (a * ia2));
		REQUIRE((a * ia) == num(1));
		REQUIRE((a * ia2).v == 1);
	}
}

TEST_CASE("Modint: negation", "[modint]") {
	auto rng = Random(20240115);

	constexpr uint32_t mod = uint32_t(998244353);
	using num = modint<mod>;

	for (int z = 0; z < 200; z++) {
		num v = rng.uniform<uint32_t>(0, mod-1);
		num nv = -v;
		REQUIRE(v + nv == num(0));
	}
}

TEST_CASE("Modint: addition/subtraction", "[modint]") {
	auto rng = Random(20240107);

	constexpr uint32_t mod = uint32_t(1e9) + 7;
	using num = modint<mod>;

	constexpr int N = 233;
	Vec<num> A(N);
	for (num& a : A) a = rng.uniform<uint32_t>(0, mod-1);
	Vec<num> pref(N+1);
	for (int i = 0; i < N; i++) {
		pref[i+1] = pref[i] + A[i];
	}

	for (int l = 0; l <= N; l++) {
		num tot = 0;
		for (int r = l; r <= N; r++) {
			REQUIRE(tot == pref[r] - pref[l]);
			if (r < N) {
				tot += A[r];
			}
		}
	}
}