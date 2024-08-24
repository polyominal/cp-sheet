// verification-helper: PROBLEM https://judge.yosupo.jp/problem/bipartitematching

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "graph/bipartite.hpp"
using namespace std;

using fast_input::Scanner;

int main() {
	auto sc = Scanner();

	int nl, nr, m;
	sc >> nl >> nr >> m;

	auto bip = Bipartite(nl, nr);
	for (int e = 0; e < m; e++) {
		int a, b;
		sc >> a >> b;
		bip.add_edge(a, b);
	}

	bip.run();

	auto matching = bip.matching();
	cout << size(matching) << '\n';
	for (auto [a, b] : matching) {
		cout << a << ' ' << b << '\n';
	}

	return 0;
}