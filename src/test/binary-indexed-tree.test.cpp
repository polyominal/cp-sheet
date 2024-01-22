#include <catch2/catch_test_macros.hpp>

#include "data-structure/binary-indexed-tree.hpp"
#include "util/random.hpp"

TEST_CASE("BIT: point add range sum", "[binary-index-tree]") {
	auto rng = Random(1145141);

	for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		using T = int64_t;
		constexpr T INF = 1e18;

		V<T> A(N);
		for (T& a : A) {
			a = rng.uniform(-INF/2, INF/2);
		}

		BIT<T> ft(A);
		constexpr int Q = 80;
		for (int q = 0; q < Q; q++) {
			for (int z = 0; z < 4; z++) {
				int p = rng.uniform(0, N-1);
				T x = rng.uniform<T>(-1e12, 1e12);
				A[p] += x;
				ft.add(p, x);
			}

			for (int l = 0; l <= N; l++) {
				T tot = 0;
				for (int r = l; r <= N; r++) {
					REQUIRE(tot == ft.sum(r) - ft.sum(l));
					if (r < N) {
						tot += A[r];
					}
				}
			}
		}
	}
}

TEST_CASE("BIT: kth search", "[binary-index-tree]") {
	auto rng = Random(20240111);

	for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 64}) {
		// sample sz elements from 0, ..., N-1
		for (int sz = 1; sz <= N; sz++) {
			set<int> samp;
			while (int(samp.size()) < sz) {
				int x = rng.uniform(0, N-1);
				samp.insert(x);
			}
			REQUIRE(int(samp.size()) == sz);

			BIT<int> bit(N);
			for (int x : samp) {
				bit.add(x, 1);
			}

			int k = 0;
			for (int x : samp) {
				REQUIRE(bit.kth_helper(k) == x);
				k++;
			}
			for (int i = sz; i <= N+5; i++) {
				REQUIRE(bit.kth_helper(k+1) == N);
			}
		}
	}
}
