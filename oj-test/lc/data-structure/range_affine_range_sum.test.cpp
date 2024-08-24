// verification-helper: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum

#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/lazy-segtree.hpp"

int main() {
	using fast_input::Scanner;
	auto sc = Scanner(stdin);

	std::ios_base::sync_with_stdio(false);

	int N, Q;
	sc >> N >> Q;

	constexpr u32 MOD = 998244353;
	using Z = ModInt<MOD>;

	struct RangeAffineMonoid {
		using S = pair<Z, int>;
		using F = pair<Z, Z>;

		constexpr S e() { return {0, 0}; }
		S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
		S mapping(F f, S a) {
			return {a.first * f.first + a.second * f.second, a.second};
		}

		constexpr F id() { return {1, 0}; }
		F composition(F f, F g) {
			return {f.first * g.first, f.second * g.first + g.second};
		}
	} m;

	auto st = LazySegtree(
		N,
		[&](int) -> RangeAffineMonoid::S {
			Z a;
			sc >> a.v;
			return {a, 1};
		},
		m);

	for (int q = 0; q < Q; q++) {
		int t, l, r;
		sc >> t >> l >> r;
		if (t == 0) {
			Z b, c;
			sc >> b.v >> c.v;
			st.apply(l, r, {b, c});
		} else if (t == 1) {
			Z tot = 0;
			st.enumerate(l, r, [&](const RangeAffineMonoid::S& s) -> void {
				tot += s.first;
			});
			std::cout << tot.v << '\n';
		}
	}

	return 0;
}