// verification-helper: PROBLEM https://judge.yosupo.jp/problem/two_edge_connected_components

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/flatten-vector.hpp"
#include "graph/two-edge-cc.hpp"

int main() {
	using namespace std;
	using fast_input::Scanner;

	auto sc = Scanner();
	int n, m;
	sc >> n >> m;
	auto edges = Vec<pair<int, int>>(2 * m);
	for (int e = 0; e < m; e++) {
		int a, b;
		sc >> a >> b;
		edges[e] = {a, b};
		edges[m + e] = {b, a};
	}
	auto g = FlattenVector<int>(n, edges);

	auto mapping = Vec<pair<int, int>>();
	int ng = two_edge_cc(
		g, [&](int t, int v) -> void { mapping.emplace_back(t, v); });
	auto groups = FlattenVector<int>(ng, mapping);

	cout << ng << '\n';
	for (int z = 0; z < ng; z++) {
		cout << size(groups[z]);
		for (int v : groups[z]) {
			cout << ' ' << v;
		}
		cout << '\n';
	}

	return 0;
}