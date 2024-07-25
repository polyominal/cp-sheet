#include <gtest/gtest.h>
#include <algebra/modint.hpp>
#include <data-structure/treap.hpp>
#include <util/random.hpp>

TEST(TreapTest, DynamicSequenceRangeAffineRangeSum) {
	auto rng = Random(20240107);

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
		constexpr u32 MOD = 998244353;
		using Z = ModInt<MOD>;
		struct Data {
			using S = Z;
			using F = pair<Z, Z>;

			S op(S a, S b) { return a + b; }
			S e() { return S(0); }
			S rev(S a) { return a; }

			S mapping_sz(F f, S a, int sz) {
				return f.first * a + f.second * sz;
			}
			F composition(F f, F g) {
				return F{f.first * g.first, f.first * g.second + f.second};
			}
			F id() { return F{1, 0}; }
		};

		TreapManager<Data, false> tm(Data{});

		vector<Z> A(N);
		for (int i = 0; i < N; i++) {
			A[i].v = rng.uniform<u32>(0, MOD - 1);
		}
		auto tr = tm.build(A);
		EXPECT_EQ(tm.size(tr), N);

		constexpr int Q = 20;
		for (int q = 0; q < Q; q++) {
			{
				int l, r;
				while (true) {
					l = rng.uniform(0, N);
					r = rng.uniform(0, N);
					if (l <= r) break;
				}

				auto tr2 = tm.split_k(tr, l);
				auto tr3 = tm.split_k(tr2, r - l);

				// now do something with the interval
				int op = rng.uniform(0, 1);
				if (op == 0) {
					std::reverse(begin(A) + l, begin(A) + r);
					tm.reverse(tr2);
				} else if (op == 1) {
					Z a = rng.uniform<uint32_t>(0, MOD - 1);
					Z b = rng.uniform<uint32_t>(0, MOD - 1);
					for (int i = l; i < r; i++) {
						A[i] *= a, A[i] += b;
					}
					tm.apply(tr2, {a, b});
				} else
					assert(false);

				tr = tm.merge(tm.merge(tr, tr2), tr3);
				EXPECT_EQ(tm.size(tr), N);
			}

			for (int l = 0; l <= N; l++) {
				Z tot = 0;
				for (int r = l; r <= N; r++) {
					auto tr2 = tm.split_k(tr, l);
					auto tr3 = tm.split_k(tr2, r - l);

					EXPECT_EQ(tm.prod(tr2), tot);

					tr = tm.merge(tm.merge(tr, tr2), tr3);
					if (r < N) {
						tot += A[r];
					}
				}
			}
		}
	}
}