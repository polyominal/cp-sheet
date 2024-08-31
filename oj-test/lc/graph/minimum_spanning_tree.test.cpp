// verification-helper: PROBLEM https://judge.yosupo.jp/problem/minimum_spanning_tree

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "graph/mst-kruskal.hpp"

int main() {
	using namespace std;
	using fast_input::Scanner;

	auto sc = Scanner();

	using E = kruskal_impl::E<u64>;
	using kruskal_impl::mst;

	int n, m;
	sc >> n >> m;
	auto edges = Vec<E>(m);
	for (auto& e : edges) {
		sc >> e.a >> e.b >> e.w;
	}

	auto mst_edges = Vec<int>();
	u64 tot = 0;
	mst(n, edges, [&](int i) {
		const E& e = edges[i];
		mst_edges.push_back(i);
		tot += e.w;
	});

	cout << tot << '\n';
	assert(int(mst_edges.size()) == n - 1);
	for (int z = 0; z < n - 1; z++) {
		cout << mst_edges[z] << " \n"[z + 1 == n - 1];
	}

	return 0;
}