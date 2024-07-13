/**
 * Author: Hanfei Chen
 * Date: 2023-08-05
 * Description: Static range composition. You need to specify
 * a compositition function $f$ and an identity element $e$
 * Time: $O(N \log N)$ building and $O(1)$ querying
 * Status: To be tested
 */

#pragma once

#include "contest/base.hpp"

template <class T, class F> struct StaticRange {
	Vec<Vec<T>> d; /// start-hash
	const F f;
	const T e;
	StaticRange(const Vec<T>& a, F f_, T e_) : f(f_), e(e_) {
		int n = int(a.size());
		int h = 0;
		while ((2 << h) < n) h++;
		d.resize(h+1);
		d[0] = a;
		for (int k = 0; k < h; k++) {
			d[k+1].resize(n, e);
			int s = 1 << (k+1);
			for (int i = s; i < n; i += 2*s) {
				T x = e;
				for (int j = i-1; j >= i-s; j--) {
					d[k+1][j] = x = f(a[j], x);
				}
				x = e;
				for (int j = i; j < i+s && j < n; j++) {
					d[k+1][j] = x = f(x, a[j]);
				}
			}
		}
	} /// end-hash

	T operator()(int l, int r) const { /// start-hash
		if (l >= r) return e;
		r--;
		if (l == r) return d[0][l];
		int k = std::bit_width<u32>(l ^ r) - 1;
		return f(d[k][l], d[k][r]);
	} /// end-hash
};