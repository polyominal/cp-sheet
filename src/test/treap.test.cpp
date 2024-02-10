#include <catch2/catch_test_macros.hpp>

#include "data-structure/treap.hpp"
#include "algebra/modint.hpp"
#include "util/random.hpp"

using namespace std;

// Work in progress
TEST_CASE("Treap: range affine range sum", "[treap]") {
	auto rng = Random(20240107);

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
		constexpr uint32_t mod = 998244353;
		using num = modint<mod>;
		struct data_t {
			using S = num;
			using F = pair<num, num>;

			S op(S a, S b) { return a + b; }
			S e() { return S(0); }
			S rev(S a) { return a; }

			S mapping_sz(F f, S a, int sz) {
				return f.first * a + f.second * sz;
			}
			F composition(F f, F g) {
				return {f.first * g.first, f.first * g.second + f.second};
			}
			F id() { return {1, 0}; }
		};

		TreapManager<data_t, false> tm(data_t{});

		vector<num> A(N);
		for (int i = 0; i < N; i++) {
			A[i] = rng.uniform<uint32_t>(0, mod-1);
		}
		auto tr = tm.build(A);
		REQUIRE(tm.size(tr) == N);

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
					reverse(A.begin() + l, A.begin() + r);
					tm.reverse(tr2);
				} else if (op == 1) {
					num a = rng.uniform<uint32_t>(0, mod-1);
					num b = rng.uniform<uint32_t>(0, mod-1);
					for (int i = l; i < r; i++) {
						A[i] *= a, A[i] += b;
					}
					tm.apply(tr2, {a, b});
				} else
					assert(false);

				tr = tm.merge(tm.merge(tr, tr2), tr3);
				REQUIRE(tm.size(tr) == N);
			}

			for (int l = 0; l <= N; l++) {
				num tot = 0;
				for (int r = l; r <= N; r++) {
					auto tr2 = tm.split_k(tr, l);
					auto tr3 = tm.split_k(tr2, r - l);

					REQUIRE(tot == tm.prod(tr2));

					tr = tm.merge(tm.merge(tr, tr2), tr3);
					if (r < N) {
						tot += A[r];
					}
				}
			}
		}
	}
}
