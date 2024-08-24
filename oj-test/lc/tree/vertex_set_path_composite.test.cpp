// verification-helper: PROBLEM https://judge.yosupo.jp/problem/vertex_set_path_composite

#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/segtree.hpp"
#include "tree/hld.hpp"

int main() {
	using fast_input::Scanner;
	auto sc = Scanner();

	int N, Q;
	sc >> N >> Q;

	using Z = ModInt<998244353>;
	using Func = pair<Z, Z>;
	struct Monoid {
		using S = Func;

		S e() const { return {1, 0}; }
		S op(const S& a, const S& b) const {
			return {b.first * a.first, b.first * a.second + b.second};
		}
	};
	struct RevMonoid {
		using S = Func;

		S e() const { return {1, 0}; }
		S op(const S& a, const S& b) const {
			return {a.first * b.first, a.first * b.second + a.second};
		}
	};

	auto F = Vec<Func>(N);
	for (auto& [c, d] : F) {
		sc >> c.v >> d.v;
	}

	auto hld = HLD(N);
	for (int e = 0; e < N - 1; e++) {
		int a, b;
		sc >> a >> b;
		hld.add_edge(a, b);
	}
	hld.build();

	const auto& ord = hld.ord;
	const auto& iord = hld.iord;
	auto m = Monoid();
	auto rm = RevMonoid();
	auto st = Segtree(N, [&](int i) -> Func { return F[ord[i]]; }, m);
	auto rst = Segtree(N, [&](int i) -> Func { return F[ord[i]]; }, rm);

	while (Q--) {
		int t;
		sc >> t;
		if (t == 0) {
			int p;
			Func f;
			sc >> p >> f.first.v >> f.second.v;
			st.set(iord[p], f);
			rst.set(iord[p], f);
		} else if (t == 1) {
			int u, v;
			Z x;
			sc >> u >> v >> x.v;
			Func f = m.e();
			hld.apply(u, v, [&](int l, int r) -> void {
				if (l > r) {
					f = m.op(f, rst.prod(r, l));
				} else if (l < r) {
					f = m.op(f, st.prod(l, r));
				}
			});
			Z res = f.first * x + f.second;
			std::cout << res.v << '\n';
		} else {
			assert(false);
		}
	}

	return 0;

	return 0;
}