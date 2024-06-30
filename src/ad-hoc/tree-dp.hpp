/**
 * Author: Hanfei Chen
 * Date: 2022-12-24
 * Description: ``Solving for all roots'' abstraction.
 * This seems to bear some huge constant factor,
 * so try out ad-hoc implementations if you get TLs
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/tree_path_composite_sum
 * - https://cses.fi/problemset/task/1133
 */

#pragma once

#include "contest/base.hpp"

template <class D, class E> struct TreeDP {
	using S = D::S;
	const Vec<Vec<E>>& g;
	int n;
	Vec<S> dp, dp2, res;
	Vec<E> par;

	TreeDP(D d, const Vec<Vec<E>>& g_) : g(g_), n(int(g.size())), dp(n), dp2(n), res(n), par(n) {
		assert(n >= 1);
		Vec<S> up(n), pref(n);

		yc([&](auto self, int v, int p) -> void { /// start-hash
			up[v] = d.make(v);
			for (auto& e : g[v]) {
				if (e != p) {
					self(e, v);
					pref[e] = up[v];
					up[v] = d.op(up[v], up[e]);
				} else {
					par[v] = e;
				}
			}
			dp[v] = up[v];
			if (p != -1) {
				up[v] = d.up(up[v], par[v]);
			}
		})(0, -1); /// end-hash

		yc([&](auto self, int v, int p, S f) -> void { /// start-hash
			for (int j = int(g[v].size())-1; j >= 0; j--) {
				auto& e = g[v][j];
				if (e == p) continue;
				dp2[e] = d.op(f, pref[e]);
				self(e, v, d.up(dp2[e], e));
				f = d.op(f, up[e]);
			}
			res[v] = f;
		})(0, -1, d.make(0)); /// end-hash
	}

	const S& operator [](int i) const {
		return res[i];
	}
};