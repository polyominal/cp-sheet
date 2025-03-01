#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2023-11-10
 * Description: A set for insertion, removal and querying the predecessor/successor of some element
 * Status: Tested with https://judge.yosupo.jp/problem/predecessor_problem
 */

#include "contest/base.hpp"

struct FastSet {
	static constexpr int B = 64;

	int n, h;
	Vec<Vec<u64>> x;
	FastSet(int n_ = 0) : n(n_) {
		int m = (n ? n : 1);
		do {
			x.push_back(Vec<u64>((m + B - 1) / B));
			m = (m + B - 1) / B;
		} while (m > 1);
		h = int(size(x));
	}  /// end-hash

	bool empty() const {  /// start-hash
		return !x[h - 1][0];
	}
	bool operator[](int i) const {
		return (x[0][i / B] >> (i % B) & 1) != 0;
	}  /// end-hash

	void set(int i) {  /// start-hash
		for (int d = 0; d < h; d++) {
			int q = i / B, r = i % B;
			x[d][q] |= u64(1) << r;
			i = q;
		}
	}  /// end-hash

	void reset(int i) {	 /// start-hash
		for (int d = 0; d < h; d++) {
			int q = i / B, r = i % B;
			x[d][q] &= ~(u64(1) << r);
			if (x[d][q]) break;
			i = q;
		}
	}  /// end-hash

	// min active j s.t. j >= i
	int next(int i) const {	 /// start-hash
		if (i >= n) return n;
		i = max(i, 0);
		for (int d = 0; d < h; d++) {
			int q = i / B, r = i % B;
			if (q >= int(size(x[d]))) break;
			u64 up = x[d][q] >> r;
			if (up) {
				i += std::countr_zero(up);
				for (int e = d - 1; e >= 0; e--) {
					i = i * B + std::countr_zero(x[e][i]);
				}
				return i;
			}
			i = q + 1;
		}
		return n;
	}  /// end-hash

	// max active j s.t. j <= i
	int prev(int i) const {	 /// start-hash
		if (i < 0) return -1;
		i = min(i, n - 1);
		for (int d = 0; d < h; d++) {
			if (i < 0) break;
			int q = i / B, r = i % B;
			u64 lo = x[d][q] << (B - 1 - r);
			if (lo) {
				i -= std::countl_zero(lo);
				for (int e = d - 1; e >= 0; e--) {
					i = i * B + B - 1 - std::countl_zero(x[e][i]);
				}
				return i;
			}
			i = q - 1;
		}
		return -1;
	}  /// end-hash

	// not tested
	void enumerate(int l, int r, std::function<void(int)> f) {
		for (int p = next(l); p < r; p = next(p + 1)) {
			f(p);
		}
	}
};
