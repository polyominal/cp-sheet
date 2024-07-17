#pragma once

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

#include "contest/base.hpp"

// REQUIRED: n >= 1 and g represents (bidirectionally) a tree
// int(E): edge -> index of its destination
// TODO:
// - subtree(v, p): subtree rooted at v with parent p
// - Avoid recursion?
template <class M, class E> struct TreeDP {
	using S = M::S;
	int n;
	Vec<S> sub, psub, res;
	Vec<E> par;
	TreeDP(M d, const Vec<Vec<E>>& g)
		: n(int(size(g))), sub(n), psub(n), res(n), par(n) {
		Vec<S> up(n), pref(n);
		auto dfs_up = [&](auto self, int v, int p) -> void { /// start-hash
			up[v] = d.make(v);
			for (const auto& e : g[v]) {
				if (e != p) {
					self(self, e, v);
					pref[e] = up[v];
					up[v] = d.op(up[v], up[e]);
				} else {
					par[v] = e;
				}
			}
			sub[v] = up[v];
			if (p != -1) {
				up[v] = d.up(up[v], par[v]);
			}
		};
		dfs_up(dfs_up, 0, -1); /// end-hash
		auto dfs_down = [&](auto self, int v, int p, S f) -> void { /// start-hash
			for (const auto& e : g[v] | std::views::reverse) {
				if (e == p) continue;
				psub[e] = d.op(f, pref[e]);
				self(self, e, v, d.up(psub[e], e));
				f = d.op(f, up[e]);
			}
			res[v] = f;
		};
		dfs_down(dfs_down, 0, -1, d.make(0)); /// end-hash
	}
	const S& operator[](int i) const {
		return res[i];
	}
};