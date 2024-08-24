#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2023-12-08
 * Description: Hopcroft–Karp algorithm that gives
 * a maximum bipartite matching.
 * \texttt{edges} should be a sequence of
 * edges $(a_i, b_i)$ such that
 * $a_i \in [n_l]$ and $b_i \in [n_r]$
 * Time: O(E \sqrt V)
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/bipartitematching (matching)
 * - https://atcoder.jp/contests/abc274/tasks/abc274_g (vertex covering)
 */

#include "contest/base.hpp"

struct Bipartite {
	int nl, nr;
	Vec<Vec<int>> g;
	Vec<int> mtl, mtr, lvl;
	Vec<bool> seen;
	Bipartite(int nl_, int nr_)
		: nl(nl_),
		  nr(nr_),
		  g(nl),
		  mtl(nl, -1),
		  mtr(nr, -1),
		  lvl(nl),
		  seen(nr) {}

	void add_edge(int a, int b) { g[a].push_back(b); }

	void run() {
		Vec<int> q;
		q.reserve(nl);
		while (true) {
			q.clear();	/// start-hash
			for (int i = 0; i < nl; i++) {
				if (mtl[i] == -1) {
					lvl[i] = 0;
					q.push_back(i);
				} else {
					lvl[i] = -1;
				}
			}
			// If there is an alternating path that
			// leads to some unmatched left-side vertex
			bool f = false;
			for (int z = 0; z < int(q.size()); z++) {
				int i = q[z];
				for (int j : g[i]) {
					int o = mtr[j];
					if (o == -1) {
						f = true;
					} else if (lvl[o] == -1) {
						lvl[o] = lvl[i] + 1;
						q.push_back(o);
					}
				}
			}
			if (!f) {
				for (int i : q) {
					for (int j : g[i]) seen[j] = true;
				}
				break;
			}  /// end-hash

			Vec<bool> done(nl);	 /// start-hash
			for (int s = 0; s < nl; s++) {
				if (mtl[s] != -1) continue;

				auto dfs = [&](auto self, int i) -> bool {
					if (done[i]) return false;
					done[i] = true;
					for (int j : g[i]) {
						int o = mtr[j];
						if (o == -1 ||
							(lvl[i] + 1 == lvl[o] && self(self, o))) {
							mtl[i] = j, mtr[j] = i;
							return true;
						}
					}
					return false;
				};
				dfs(dfs, s);
			}  /// end-hash
		}
	}

	Vec<pair<int, int>> matching() {  /// start-hash
		Vec<pair<int, int>> res;
		for (int i = 0; i < nl; i++) {
			int j = mtl[i];
			if (j != -1) res.emplace_back(i, j);
		}
		return res;
	}  /// end-hash

	pair<Vec<int>, Vec<int>> vertex_cover() {  /// start-hash
		Vec<int> lvs, rvs;
		for (int i = 0; i < nl; i++) {
			if (lvl[i] == -1) lvs.push_back(i);
		}
		for (int j = 0; j < nr; j++) {
			if (seen[j]) rvs.push_back(j);
		}
		return {lvs, rvs};
	}  /// end-hash
};