#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2023-09-11
 * Description: Works iff, for all $a \le b < c \le d$, $g(a,c) \ge g(b,c) \implies g(a,d) \ge g(b,d)$.
 * (Or if $g(a,c) + g(b,d) \le g(a,d) + g(b,c)$.)
 * Source: Largely drawn from https://nyaannyaan.github.io/library/dp/monge-shortest-path.hpp
 * Status: Somewhat tested
 */

#include "contest/base.hpp"

template <class T, class C>
Vec<T> monge_shortest_path(int n, C g, const T inf) {
	Vec<T> dp(n + 1, inf);	/// start-hash
	dp[0] = 0;
	Vec<int> x(n + 1, 0);
	auto upd = [&](int s, int t) -> void {
		if (s >= t) return;
		T v = dp[s] + g(s, t);
		if (v < dp[t]) {
			dp[t] = v;
			x[t] = s;
		}
	};
	upd(0, n);										   /// end-hash
	auto rec = [&](auto self, int l, int r) -> void {  /// start-hash
		if (l + 1 >= r) return;
		int m = (l + r) / 2;
		for (int i = x[l]; i <= x[r]; i++) {
			upd(i, m);
		}
		self(self, l, m);
		for (int i = l + 1; i <= m; i++) {
			upd(i, r);
		}
		self(self, m, r);
	};
	rec(rec, 0, n);	 /// end-hash
	return dp;
}