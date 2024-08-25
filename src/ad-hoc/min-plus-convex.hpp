#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2023-10-03
 * Description: Given $a_0, \ldots, a_{N-1}$ and $b_0, \ldots, b_{M-1}$
 * such that $a_{i+1} - a_i \le a_{i+2} - a_{i+1}$, returns $c_0, \ldots, c_{(N-1) + (M-1)}$
 * such that $c_k = \min_{i+j=k} a_i + b_j$
 * Status: Tested with https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
 */

#include "ad-hoc/monotone-minima.hpp"

// a convex and b arbitrary
template <class T> Vec<T> min_plus_convex(const Vec<T>& a, const Vec<T>& b) {
	int n = int(size(a)), m = int(size(b));
	if (!n || !m) return {};
	auto x = monotone_minima(n + m - 1, m, [&](int i, int j, int k) -> bool {
		if (i < k) return true;
		if (i - j >= n) return false;
		return a[i - j] + b[j] <= a[i - k] + b[k];
	});
	auto res = Vec<T>(n + m - 1);
	for (int i = 0; i < n + m - 1; i++) {
		res[i] = a[i - x[i]] + b[x[i]];
	}
	return res;
}