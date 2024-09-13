// verification-helper: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A

#include <ios>
#include "graph/maxflow.hpp"

int main() {
	using namespace std;

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	struct E {
		int to;
		int rev;
		int cap;
	};
	auto g = Vec<Vec<E>>(n);
	auto add_edge = [&](int from, int to, int cap) {
		g[from].push_back({to, int(g[to].size()), cap});
		g[to].push_back({from, int(g[from].size()) - 1, 0});
	};

	for (int _ = 0; _ < m; _++) {
		int from, to, cap;
		cin >> from >> to >> cap;
		add_edge(from, to, cap);
	}

	MaxFlow<int> info = get_mf(g, 0, n - 1, 0);
	cout << info.flow << '\n';

	return 0;
}