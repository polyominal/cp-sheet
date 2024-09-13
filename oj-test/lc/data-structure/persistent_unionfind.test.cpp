// verification-helper: PROBLEM https://judge.yosupo.jp/problem/persistent_unionfind

#include "data-structure/persistent-array.hpp"
using namespace std;

struct Data {
	int v = -1;
	Data() {}
	Data(int a) : v(a) {}

	operator int() const { return v; }
};

int main() {
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	auto pa = PersistentArray<Data>();
	vector<int> roots = {pa.build(N)};
	auto getpar = [&](int rt, int a) -> int {
		assert(rt >= 0);

		while (true) {
			int p = pa.get(rt, a);
			if (p < 0) break;
			a = p;
		}
		return a;
	};
	auto merge = [&](int rt, int a, int b) -> int {
		assert(rt >= 0);

		a = getpar(rt, a);
		b = getpar(rt, b);

		if (a == b) return rt;

		int sa = pa.get(rt, a);
		int sb = pa.get(rt, b);
		if (sa > sb) {
			swap(a, b);
			swap(sa, sb);
		}
		rt = pa.set(rt, a, sa + sb);
		rt = pa.set(rt, b, a);
		return rt;
	};

	while (Q--) {
		int t, k, u, v;
		cin >> t >> k >> u >> v;
		roots.push_back(-1);
		if (t == 0) {
			roots.back() = merge(roots[k + 1], u, v);
		} else if (t == 1) {
			cout << int(getpar(roots[k + 1], u) == getpar(roots[k + 1], v))
				 << '\n';
		} else {
			assert(false);
		}
	}

	return 0;
}