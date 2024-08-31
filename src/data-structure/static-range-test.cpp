#include <gtest/gtest.h>
#include <algebra/modint.hpp>
#include <data-structure/static-range.hpp>
#include <util/random.hpp>

namespace testing {

TEST(TestStaticRangeProduct, StaticRangeCompositionMinMax) {
	auto rng = Random(1145141);

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = int64_t;
		constexpr T INF = 1e18;

		Vec<T> A(N);
		for (T& a : A) {
			a = rng.uniform(-INF / 2, INF / 2);
		}

		StaticRange sr_min(A, [](T a, T b) { return min(a, b); }, INF);
		StaticRange sr_max(A, [](T a, T b) { return max(a, b); }, -INF);
		for (int l = 0; l <= N; l++) {
			T mi = INF;
			T ma = -INF;
			for (int r = l; r <= N; r++) {
				EXPECT_EQ(mi, sr_min.prod(l, r));
				EXPECT_EQ(ma, sr_max.prod(l, r));
				if (r < N) {
					mi = min(mi, A[r]);
					ma = max(ma, A[r]);
				}
			}
		}
	}
}

TEST(TestStaticRangeProduct, StaticRangeCompositionProductMod998244353) {
	auto rng = Random(1145141);

	using num = ModInt<998244353>;

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = num;
		const T e(1);

		Vec<T> A(N);
		for (T& a : A) {
			a = rng.uniform<uint32_t>(0, num::get_mod() - 1);
		}

		StaticRange sr_prod(A, [](T a, T b) { return a * b; }, e);
		for (int l = 0; l <= N; l++) {
			T p = e;
			for (int r = l; r <= N; r++) {
				EXPECT_EQ(p, sr_prod.prod(l, r));
				if (r < N) {
					p *= A[r];
				}
			}
		}
	}
}

TEST(TestStaticRangeProduct, StaticRangeCompositionAffineMod998244353) {
	auto rng = Random(20240115);

	using num = ModInt<998244353>;

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = pair<num, num>;
		const T e(1, 0);
		const auto op = [](T a, T b) {
			return T(a.first * b.first, a.second * b.first + b.second);
		};

		Vec<T> A(N);
		for (auto& [a, b] : A) {
			a = rng.uniform<uint32_t>(0, num::get_mod() - 1);
			b = rng.uniform<uint32_t>(0, num::get_mod() - 1);
		}

		StaticRange sr_affine(A, op, e);
		for (int l = 0; l <= N; l++) {
			T p = e;
			for (int r = l; r <= N; r++) {
				EXPECT_EQ(p, sr_affine.prod(l, r));
				if (r < N) {
					p = op(p, A[r]);
				}
			}
		}
	}
}

}  // namespace testing