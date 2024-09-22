#include <gtest/gtest.h>
#include <contest/base.hpp>
#include <data-structure/binary-indexed-tree.hpp>
#include <util/random.hpp>

namespace testing {

TEST(BinaryIndexedTreeTest, PointAddRangeSum) {
	auto rng = Random(1145141);

	for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = int64_t;
		constexpr T INF = 1e18;

		auto A = Vec<T>(N);
		for (T& a : A) {
			a = rng.uniform(-INF / 2, INF / 2);
		}

		auto ft = BIT<T>(A);
		constexpr int Q = 20;
		for (int q = 0; q < Q; q++) {
			int num_updates = rng.uniform(0, 4);

			for (int z = 0; z < num_updates; z++) {
				int p = rng.uniform(0, N - 1);
				T x = rng.uniform<T>(-1e12, 1e12);
				A[p] += x;
				ft.add(p, x);
			}

			for (int l = 0; l <= N; l++) {
				T tot = 0;
				for (int r = l; r <= N; r++) {
					EXPECT_EQ(tot, ft.sum(r) - ft.sum(l));
					if (r < N) {
						tot += A[r];
					}
				}
			}
		}
	}
}

TEST(BinaryIndexedTreeTest, KthSearch) {
	auto rng = Random(20240718);

	for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 64}) {
		// sample sz elements from 0, ..., N-1
		for (int sz = 1; sz <= N; sz++) {
			auto samp = set<int>();
			while (int(size(samp)) < sz) {
				int x = rng.uniform(0, N - 1);
				samp.insert(x);
			}
			EXPECT_EQ(int(size(samp)), sz);

			auto bit = BIT<int>(N);
			for (int x : samp) {
				bit.add(x, 1);
			}

			int k = 0;
			for (int x : samp) {
				EXPECT_EQ(bit.kth_helper(k), x);
				k++;
			}
			for (int i = sz; i <= N + 5; i++) {
				EXPECT_EQ(bit.kth_helper(k + 1), N);
			}
		}
	}
}

}  // namespace testing