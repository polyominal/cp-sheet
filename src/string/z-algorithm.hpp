/**
 * Author: Hanfei Chen
 * Date: 2024-01-03
 * Source: https://github.com/yosupo06/Algorithm/blob/master/src/string/zalgo.hpp
 * Description: Returns $r_0, \ldots, r_N$ such that $s[0..r_i) = s[i..i+r_i)$.
 * In particular, $r_0 = N$ and $r_N = 0$
 * Time: O(N)
 * Status: Tested with https://judge.yosupo.jp/problem/zalgorithm
 */

#pragma once

#include "contest/base.hpp"

template <class S> V<int> z_algo(const S& s) {
	int n = int(s.size());
	V<int> res(n+1);
	for (int i = 1, j = 0; i <= n; i++) {
		int& k = res[i];
		if (j + res[j] <= i) {
			k = 0;
		} else {
			k = min(res[j] + j - i, res[i-j]);
		}
		while (i+k < n && s[k] == s[i+k]) k++;
		if (j + res[j] < i + res[i]) j = i;
	}
	res[0] = n;
	return res;
}

