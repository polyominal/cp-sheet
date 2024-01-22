#include <catch2/catch_test_macros.hpp>

#include "data-structure/static-range.hpp"
#include "util/random.hpp"
#include "algebra/modint.hpp"

TEST_CASE("Static range composition: min/max", "[static-range]") {
	auto rng = Random(1145141);

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = int64_t;
		constexpr T INF = 1e18;

		V<T> A(N);
		for (T& a : A) {
			a = rng.uniform(-INF/2, INF/2);
		}

		StaticRange sr_min(A, [](T a, T b) { return min(a, b); }, INF);
		StaticRange sr_max(A, [](T a, T b) { return max(a, b); }, -INF);
		for (int l = 0; l <= N; l++) {
			T mi = INF;
			T ma = -INF;
			for (int r = l; r <= N; r++) {
				REQUIRE(mi == sr_min(l, r));
				REQUIRE(ma == sr_max(l, r));
				if (r < N) {
					mi = min(mi, A[r]);
					ma = max(ma, A[r]);
				}
			}
		}
	}
}

TEST_CASE("Static range composition: product mod 998244353", "[static-range]") {
	auto rng = Random(1145141);

	using num = mint<998244353>;

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = num;
		const T e(1);

		V<T> A(N);
		for (T& a : A) {
			a = rng.uniform<uint32_t>(0, num::get_mod()-1);
		}

		StaticRange sr_prod(A, [](T a, T b) { return a * b; }, e);
		for (int l = 0; l <= N; l++) {
			T p = e;
			for (int r = l; r <= N; r++) {
				REQUIRE(p == sr_prod(l, r));
				if (r < N) {
					p *= A[r];
				}
			}
		}
	}
}

TEST_CASE("Static range composition: affine mod 998244353", "[static-range]") {
	auto rng = Random(20240115);

	using num = mint<998244353>;

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = pair<num, num>;
		const T e(1, 0);
		const auto op = [](T a, T b) {
			return T(a.first * b.first, a.second * b.first + b.second);
		};

		V<T> A(N);
		for (auto& [a, b] : A) {
			a = rng.uniform<uint32_t>(0, num::get_mod()-1);
			b = rng.uniform<uint32_t>(0, num::get_mod()-1);
		}

		StaticRange sr_affine(A, op, e);
		for (int l = 0; l <= N; l++) {
			T p = e;
			for (int r = l; r <= N; r++) {
				REQUIRE(p == sr_affine(l, r));
				if (r < N) {
					p = op(p, A[r]);
				}
			}
		}
	}
}
