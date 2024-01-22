#include "contest/base.hpp"

template <class E> VV<int> block_cut_tree(int n, const VV<E>& g) {
	VV<int> tr(n);
	auto add = [&](int b, int v) -> void {
		tr[b].push_back(v);
		tr[v].push_back(b);
	};

	V<int> stk; stk.reserve(n);
	V<int> idx(n, -1);
	int t = 0;
	for (int s = 0; s < n; s++) {
		if (idx[s] != -1) continue;
		yc([&](auto self, int v, int p) -> int {
			stk.push_back(v);
			idx[v] = t++;
			int low = idx[v] = t++;
			int c = 0;
			for (int w : g[v]) {
				if (w == p) continue;
				if (idx[w] == -1) {
					c++;
					auto z = stk.size();
					int nlow = self(w, v);
					low = min(low, nlow);
					if ((p == -1 && c > 1) || (p != -1 && idx[v] <= nlow)) {
						int b = int(tr.size());
						tr.resize(b+1);
						add(b, v);
						while (z < stk.size()) {
							add(b, stk.back());
							stk.pop_back();
						}
					}
				} else {
					low = min(low, idx[w]);
				}
			}
			return low;
		})(s, -1);
		int b = int(tr.size());
		tr.resize(b+1);
		for (int v : stk) add(b, v);
		stk.clear();
	}

	return tr;
}