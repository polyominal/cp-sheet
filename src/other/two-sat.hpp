#pragma once

/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit inversions (\texttt{\tilde{}x})
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.set_value(2); // Var 2 is true
 *  ts.at_most_one({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E)
 * Status: Tested with https://judge.yosupo.jp/problem/two_sat
 */

#include "data-structure/flatten-vector.hpp"

struct TwoSat {
	int n;
	Vec<pair<int, int>> edges;
	TwoSat(int n_ = 0) : n(n_) {}

	int add_var() { return n++; }
	void either(int a, int b) {
		a = max(2 * a, -1 - 2 * a);
		b = max(2 * b, -1 - 2 * b);
		edges.emplace_back(a ^ 1, b);
		edges.emplace_back(b ^ 1, a);
	}
	void set_value(int x) { either(x, x); }
	// NOT VERIFIED
	void at_most_one(const Vec<int>& vs) {
		if (size(vs) <= 1) return;
		int cur = ~vs[0];
		for (int v : vs | std::views::drop(2)) {
			int nxt = add_var();
			either(cur, ~v);
			either(cur, nxt);
			either(~v, nxt);
			cur = ~nxt;
		}
		either(cur, ~vs[1]);
	}
	Opt<Vec<i8>> solve() {
		auto r = Vec<i8>(n, -1);
		auto g = FlattenVector<int>(2 * n, std::move(edges));
		auto q = Vec<int>();
		auto bfs = [&](int s) -> bool {
			q.clear();
			q.push_back(s);
			r[s / 2] = !(s % 2);
			for (size_t z = 0; z < size(q); z++) {
				int v = q[z];
				for (int w : g[v]) {
					if (r[w / 2] == -1) {
						r[w / 2] = !(w % 2);
						q.push_back(w);
					} else if (r[w / 2] == w % 2) {
						return false;
					}
				}
			}
			return true;
		};
		for (int i = 0; i < n; i++) {
			if (r[i] != -1 || bfs(2 * i + 1)) continue;
			for (int v : q) r[v / 2] = -1;
			if (!bfs(2 * i)) return std::nullopt;
		}
		return r;
	}
};