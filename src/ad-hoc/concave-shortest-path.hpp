#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2023-08-31
 * Description: Works iff, for all $a \le b < c \le d$, $g(a,c) \le g(b,c) \implies g(a,d) \le g(b,d)$.
 * (Or if $g(a,c) + g(b,d) \ge g(a,d) + g(b,c)$.)
 * Status: Wish you luck
 */

#include "contest/base.hpp"

template <class T, class F> Vec<T> concave_shortest_path(int n, F g) {
	Vec<T> dp(n + 1);  /// start-hash
	struct I {
		int p, l, r;
		I(int p_, int l_, int r_) : p(p_), l(l_), r(r_) {}
	};
	Vec<I> v = {I(0, 1, n)};
	v.reserve(n + 1);
	auto f = [&](int s, int t) { return dp[s] + g(s, t); };	 /// end-hash
	for (int i = 1; i <= n; i++) {							 /// start-hash
		dp[i] = f(v.back().p, i);
		if (v.back().r == i) {
			v.pop_back();
		} else {
			v.back().l++;
		}
		while (true) {
			if (v.empty()) break;
			if (f(i, v.back().r) < f(v.back().p, v.back().r)) {
				v.pop_back();
			} else {
				break;
			}
		}
		if (v.empty()) {
			v.emplace_back(i, i + 1, n);
		} else {
			int l = v.back().l - 1, r = v.back().r;
			while (r - l > 1) {
				int m = (l + r) / 2;
				if (f(v.back().p, m) <= f(i, m)) {
					r = m;
				} else {
					l = m;
				}
			}
			v.back().l = r;
			if (r != i + 1) v.emplace_back(i, i + 1, r - 1);
		}
	}  /// end-hash
	return dp;
}