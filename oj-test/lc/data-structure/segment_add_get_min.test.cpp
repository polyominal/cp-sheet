// verification-helper: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min

#include "ad-hoc/li-chao-segtree.hpp"

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	using namespace lichao_impl;

	Node* rt = nullptr;

	for (int i = 0; i < N; i++) {
		int l, r;
		cin >> l >> r;
		i64 a, b;
		cin >> a >> b;
		rt = insert_outer({-a, -b}, rt, LO, HI, l, r);
	}

	for (int q = 0; q < Q; q++) {
		int t;
		cin >> t;
		if (t == 0) {
			int l, r;
			cin >> l >> r;
			i64 a, b;
			cin >> a >> b;
			rt = insert_outer({-a, -b}, rt, LO, HI, l, r);
		} else if (t == 1) {
			int p;
			cin >> p;
			auto res = -point_query(p, rt, LO, HI);
			if (res == INF) {
				cout << "INFINITY" << '\n';
			} else {
				cout << res << '\n';
			}
		} else {
			assert(false);
		}
	}

	return 0;
}