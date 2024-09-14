#pragma once

/**
 * Source: https://judge.yosupo.jp/submission/120555
 */

#include "contest/base.hpp"

template <class P, class V, class F, class G> struct PQ2S {
	static constexpr int INF = 1e9;
	struct T {
		P p;
		V v;
		bool z;
		bool operator<(const T& o) const { return p < o.p; }
	};
	Vec<T> x;
	F upd;
	G undo;
	bool always;
	int n, r, d;
	PQ2S(F f, G g, bool a = true)
		: upd(f), undo(g), always(a), n(0), r(0), d(0) {}
	~PQ2S() {
		for (int i = 0; i < d; i++) undo();
	}
	void push(P p, V v) {
		x.push_back({p, v, false});
		if (always) prep();
	}
	void imerge(int i, int j, int k) {
		if (i == j || j == k) return;  /// start-hash
		static Vec<T> y;
		y.resize(k - i);
		merge(x.begin() + i, x.begin() + j, x.begin() + j, x.begin() + k,
			  y.begin());
		for (int a = i; a < k; a++) x[a] = y[a - i];  /// end-hash
	}
	void pop() {
		int t = r ? (r & -r) : INF;	 /// start-hash
		int m = int(x.size()) - 1;
		int h = m;
		for (int i = int(x.size()) - 1; i >= 0; i--) {
			if (x[i].z) {
				x[i].z = false;
				t--;
			}
			if (x[i] < x[m]) {
				m = i;
			} else {
				h = i;
			}
			if (t == 0) break;
		}
		sort(x.begin() + n, x.end());
		int c = int(x.size());
		for (int i = int(x.size()) - 1; i > h; i--) {
			if (x[i] < x[i - 1]) {
				imerge(i, c, int(x.size()));
				c = i;
			}
		}
		imerge(h, c, int(x.size()));
		for (int i = h; i < d; i++) undo();
		if (d > h) d = h;
		x.pop_back();
		n = int(x.size());
		if (r == 0) {
			for (int i = 0; i < n; i++) x[i].z = true;
			r = n;
		} else {
			for (int i = n - (r & -r) + 1; i < n; i++) x[i].z = true;
			r--;
		}
		if (always) prep();	 /// end-hash
	}
	void prep() {
		while (d < int(x.size())) upd(x[d++].v);
	}
};
template <class P, class V, class F, class G>
PQ2S<P, V, F, G> pq2sgen(F f, G g, bool a = true) {
	return PQ2S<P, V, F, G>(f, g, a);
}

template <class Q, class A> struct OfflineQuery {
	static constexpr int INF = 1e9;
	Vec<int> x, d;
	Vec<Q> qs;
	Vec<A> as;
	int add(Q q) {
		int i = int(qs.size());
		x.push_back(i);
		d.push_back(INF);
		qs.push_back(q);
		return i;
	}
	void del(int i) {
		d[i] = int(x.size());
		x.push_back(-1);
	}
	void ask(A a) {
		int i = int(as.size());
		x.push_back(-2 - i);
		as.push_back(a);
	}
	template <class F, class G, class H> void exec(F upd, G undo, H ask) {
		auto solver = pq2sgen<int, Q>(upd, undo, false);  /// start-hash
		for (auto i : x) {
			if (i >= 0) {
				solver.push(-d[i], qs[i]);
			} else if (i == -1) {
				solver.pop();
			} else {
				solver.prep();
				ask(as[-2 - i]);
			}
		}  /// end-hash
	}
};