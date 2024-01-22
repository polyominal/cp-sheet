/**
 * Author: Hanfei Chen
 * Date: 2023-07-19
 * Description: Supports computing partial sum $a_0 + \ldots + a_{i-1}$
 * and incrementing some $a_i$ by $v$
 * Time: Both operations are O(\log N)
 * Status:
 * - Basic operations tested with https://judge.yosupo.jp/problem/point_add_range_sum
 * - \texttt{kth} to be tested
 */

#pragma once

#include "contest/base.hpp"

template <class T> struct BIT {
	V<T> x;
	int s;
	BIT(int n) { build(n); }
	BIT(const V<T>& a) { build(a); }

	void build(int n) { /// start-hash
		x.clear();
		x.resize(s = n);
	} /// end-hash

	void build(const V<T>& a) { /// start-hash
		build(int(a.size()));
		copy(a.begin(), a.end(), x.begin());
		for (int i = 0; i < s; i++) {
			int j = i | (i+1);
			if (j < s) x[j] += x[i];
		}
	} /// end-hash

	void add(int i, T v) { /// start-hash
		for (; i < s; i |= i+1) x[i] += v;
	}
	T sum(int i) {
		T res = 0;
		for (; i; i &= i-1) res += x[i-1];
		return res;
	} /// end-hash

	// Slightly tested; requires s >= 1
	int kth(T k) { /// start-hash
		int cur = 0;
		for (int i = 31 - __builtin_clz(s); i >= 0; i--) {
			int nxt = cur + (1 << i);
			if (nxt <= s && x[nxt-1] <= k) {
				k -= x[nxt-1];
				cur = nxt;
			}
		}
		return cur;
	} /// end-hash

	int kth_helper(T k, int i = 0) { return kth(k + sum(i)); }
};
