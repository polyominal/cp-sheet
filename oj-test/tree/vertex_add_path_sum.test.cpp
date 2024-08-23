// verification-helper: PROBLEM https://judge.yosupo.jp/problem/vertex_add_path_sum

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/binary-indexed-tree.hpp"
#include "tree/hld.hpp"

int main() {
	using fast_input::Scanner;
	auto sc = Scanner();

	int N, Q;
	sc >> N >> Q;

	auto A = Vec<i64>(N);
	for (i64& a : A) {
		sc >> a;
	}

	auto hld = HLD(N);
	for (int e = 0; e < N - 1; e++) {
		int a, b;
		sc >> a >> b;
		hld.add_edge(a, b);
	}
	hld.build();

	const auto& iord = hld.iord;

	auto bit = BIT<i64>(N);
	for (int v = 0; v < N; v++) {
		bit.add(iord[v], A[v]);
	}

	while (Q--) {
		int t;
		sc >> t;
		if (t == 0) {
			int p;
			i64 x;
			sc >> p >> x;
			bit.add(iord[p], x);
		} else if (t == 1) {
			int u, v;
			sc >> u >> v;
			i64 tot = 0;
			hld.apply(u, v, [&](int l, int r) -> void {
				if (l > r) {
					std::swap(l, r);
				}
				tot += bit.sum(r) - bit.sum(l);
			});
			std::cout << tot << '\n';
		} else {
			assert(false);
		}
	}

	return 0;
}