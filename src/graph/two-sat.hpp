/**
 * Author: Emil Lenngren, Simon Lindholm (edited by Hanfei Chen)
 * Date: 2011-11-29
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x})
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

#pragma once

#include "contest/base.hpp"

struct TwoSat {
	int n;
	VV<int> g;
	TwoSat(int n_ = 0) : n(n_), g(2*n) {}

	int add_var() {
		g.emplace_back(), g.emplace_back();
		return n++;
	}

	void either(int a, int b) { /// start-hash
		a = max(2*a, -1-2*a);
		b = max(2*b, -1-2*b);
		g[a^1].push_back(b);
		g[b^1].push_back(a);
	} /// end-hash

	void set_value(int x) {
		either(x, x);
	}

	void at_most_one(const V<int>& vs) { /// start-hash
		int m = int(vs.size());
		if (m <= 1) return;
		int cur = ~vs[0];
		for (int i = 2; i < m; i++) {
			int nxt = add_var();
			either(cur, ~vs[i]);
			either(cur, nxt);
			either(~vs[i], nxt);
			cur = ~nxt;
		}
		either(cur, ~vs[1]);
	} /// end-hash

	optional<V<bool>> solve() { /// start-hash
		V<int> idx(2*n, -1), comp(2*n, -1), stk;
		int tm = 0;
		V<char> r(n, -1); /// end-hash

		for (int s = 0; s < 2*n; s++) { /// start-hash
			if (comp[s] != -1) continue;

			yc([&](auto self, int i) -> int {
				int low = idx[i] = tm++;
				stk.push_back(i);
				for (auto& j : g[i]) {
					if (comp[j] != -1) continue;
					low = min(low, idx[j] == -1 ? self(j) : idx[j]);
				}
				tm++;
				if (low == idx[i]) {
					while (true) {
						int z = stk.back(); stk.pop_back();
						comp[z] = tm;
						if (r[z>>1] == -1) r[z>>1] = !(z&1);
						if (i == z) break;
					}
				}
				return idx[i] = low;
			})(s);
		} /// end-hash

		for (int i = 0; i < n; i++) { /// start-hash
			if (comp[2*i] == comp[2*i+1]) return {};
		}
		V<bool> res(n);
		for (int i = 0; i < n; i++) res[i] = bool(r[i]);
		return res; /// end-hash
	}
};