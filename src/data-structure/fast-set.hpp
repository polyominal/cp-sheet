/**
 * Author: Hanfei Chen
 * Date: 2023-11-10
 * Description: A set for insertion, removal and querying the predecessor/successor of some element
 * Status: Tested with https://judge.yosupo.jp/problem/predecessor_problem
 */

#pragma once

#include "contest/base.hpp"

struct FastSet {
	using U = uint64_t; /// start-hash
	int n, h;
	VV<U> x;
	FastSet(int n_ = 0) : n(n_) {
		int m = (n ? n : 1);
		do {
			x.push_back(V<U>((m + 63) >> 6));
			m = (m + 63) >> 6;
		} while (m > 1);
		h = int(x.size());
	} /// end-hash

	bool empty() const { /// start-hash
		return !x[h-1][0];
	}
	bool operator [](int i) const {
		return (x[0][i >> 6] >> (i & 63)) & 1;
	} /// end-hash

	void set(int i) { /// start-hash
		for (int d = 0; d < h; d++) {
			int q = i >> 6, r = i & 63;
			x[d][q] |= U(1) << r;
			i = q;
		}
	} /// end-hash

	void reset(int i) { /// start-hash
		for (int d = 0; d < h; d++) {
			int q = i >> 6, r = i & 63;
			if ((x[d][q] &= ~(U(1) << r))) break;
			i = q;
		}
	} /// end-hash

	// min active j s.t. j >= i
	int next(int i) const { /// start-hash
		if (i >= n) return n;
		i = max(i, 0);
		for (int d = 0; d < h; d++) {
			int q = i >> 6, r = i & 63;
			if (q >= int(x[d].size())) break;
			U up = x[d][q] >> r;
			if (up) {
				i += __builtin_ctzll(up);
				for (int e = d-1; e >= 0; e--) {
					i = i << 6 | __builtin_ctzll(x[e][i]);
				}
				return i;
			}
			i = q+1;
		}
		return n;
	} /// end-hash

	// max active j s.t. j <= i
	int prev(int i) const { /// start-hash
		if (i < 0) return -1;
		i = min(i, n-1);
		for (int d = 0; d < h; d++) {
			if (i < 0) break;
			int q = i >> 6, r = i & 63;
			U lo = x[d][q] << (63-r);
			if (lo) {
				i -= __builtin_clzll(lo);
				for (int e = d-1; e >= 0; e--) {
					i = i << 6 | (63 - __builtin_clzll(x[e][i]));
				}
				return i;
			}
			i = q-1;
		}
		return -1;
	} /// end-hash

	// not tested
	template <class F> void enumerate(int l, int r, F f) {
		for (int p = next(l); p < r; p = next(p+1)) {
			f(p);
		}
	}
};
