// verification-helper: PROBLEM https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum

#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/treap.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	using fast_input::Scanner;
	auto sc = Scanner(stdin);

	int N, Q;
	sc >> N >> Q;

	constexpr u32 MOD = 998244353;
	using Z = ModInt<MOD>;
	struct Data {
		using S = Z;
		using F = pair<Z, Z>;

		S op(S a, S b) { return a + b; }
		S e() { return S(0); }
		S rev(S a) { return a; }

		S mapping_sz(F f, S a, int sz) { return f.first * a + f.second * sz; }
		F composition(F f, F g) {
			return F{f.first * g.first, f.first * g.second + f.second};
		}
		F id() { return F{1, 0}; }
	};
	auto tm = TreapManager<Data, false>(Data(), N + Q);

	auto A = Vec<Z>(N);
	for (auto& a : A) {
		sc >> a.v;
	}
	auto tr = tm.build(A);

	for (int q = 0; q < Q; q++) {
		int t;
		sc >> t;

		if (t == 0) {
			int i;
			Z x;
			sc >> i >> x.v;

			auto tr2 = tm.split_k(tr, i);
			tr = tm.merge(tr, tm.merge(tm.make_single(x), tr2));
		} else if (t == 1) {
			int i;
			sc >> i;

			auto tr2 = tm.split_k(tr, i);
			auto tr3 = tm.split_k(tr2, 1);
			tr = tm.merge(tr, tr3);
		} else if (t == 2) {
			int l, r;
			sc >> l >> r;

			auto tr2 = tm.split_k(tr, l);
			auto tr3 = tm.split_k(tr2, r - l);
			tm.reverse(tr2);
			tr = tm.merge(tr, tm.merge(tr2, tr3));
		} else if (t == 3) {
			int l, r;
			Data::F f;
			sc >> l >> r >> f.first.v >> f.second.v;

			auto tr2 = tm.split_k(tr, l);
			auto tr3 = tm.split_k(tr2, r - l);
			tm.apply(tr2, f);
			tr = tm.merge(tr, tm.merge(tr2, tr3));
		} else if (t == 4) {
			int l, r;
			sc >> l >> r;

			auto tr2 = tm.split_k(tr, l);
			auto tr3 = tm.split_k(tr2, r - l);
			std::cout << tm.prod(tr2).v << '\n';
			tr = tm.merge(tr, tm.merge(tr2, tr3));
		} else {
			assert(false);
		}
	}

	return 0;
}