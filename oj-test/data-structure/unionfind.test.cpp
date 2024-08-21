// verification-helper: PROBLEM https://judge.yosupo.jp/problem/unionfind

#include "data-structure/unionfind.hpp"
#include <ios>
#include "contest/fast-input.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	using fast_input::Scanner;
	auto sc = Scanner(stdin);

	int N, Q;
	sc.read(N, Q);

	auto uf = UnionFind(N);
	while (Q--) {
		int t, u, v;
		sc.read(t, u, v);
		if (t == 0) {
			uf.unite(u, v);
		} else {
			std::cout << uf.same(u, v) << '\n';
		}
	}

	return 0;
}