/**
 * Author: Hanfei Chen
 * Date: 2023-10-03
 * Description: Given an $N \times M$ matrix $A$, returns $m_i = \mathrm{argmin}_{j} A_{i,j}$ given
 * that $m_0, \ldots, m_{N-1}$ is non-decreasing
 * Status: Slightly tested
 */

#pragma once

#include "contest/base.hpp"

// f(i, j, k) := [A_{i, j} <= A_{i, k}], given j < k
template <class F> Vec<int> monotone_minima(int n, int m, F f) {
	Vec<int> res(n);
	yc([&](auto self, int s, int e, int l, int r) -> void {
		if (s == e) return;
		int i = (s+e)/2;
		int b = l;
		for (int k = l+1; k < r; k++) {
			if (!f(i, b, k)) b = k;
		}
		res[i] = b;
		self(s, i, l, b+1);
		self(i+1, e, b, r);
	})(0, n, 0, m);
	return res;
}