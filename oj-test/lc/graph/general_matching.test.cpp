// verification-helper: PROBLEM https://judge.yosupo.jp/problem/general_matching

#include "graph/matching.hpp"

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	auto mm = MaxMatching(n);
	for (int _ = 0; _ < m; _++) {
		int a, b;
		cin >> a >> b;
		mm.add_edge(a, b);
	}

	auto res = mm.max_matching();
	cout << res.size() << '\n';
	for (auto [a, b] : res) {
		cout << a << ' ' << b << '\n';
	}

	return 0;
}