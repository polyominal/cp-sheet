/**
 * Author: Hanfei Chen
 * Description: Gaussian elimination and stuff.
 * \texttt{solve\_lineareq} returns the pair (some particular solution, a basis of the null space).
 * Status: Tested with https://open.kattis.com/problems/equationsolver (float point), https://judge.yosupo.jp/problem/system_of_linear_equations (modint)
 */

#pragma once

#include "algebra/modint.hpp"
#include "contest/base.hpp"

namespace matrix {

template <class T> using F_better = std::function<bool(T, T)>;

template <class T> using F_zero = std::function<bool(T)>;

template <bool rref = false, class T>
pair<int, T> sweep(Vec<Vec<T>>& a, F_better<T> fb, F_zero<T> fz, int c = -1) {
	int h = int(a.size());
	if (!h) return {0, 0};
	int w = int(a[0].size());

	if (c == -1) c = w;	 /// start-hash
	int r = 0;
	T det = 1;
	for (int j = 0; j < c; j++) {
		int p = -1;
		for (int i = r; i < h; i++) {
			if (p == -1 || fb(a[i][j], a[p][j])) p = i;
		}
		if (p == -1 || fz(a[p][j])) {
			det = 0;
			continue;
		}
		if (r != p) {
			det = -det;
			swap(a[r], a[p]);
		}
		auto& ar = a[r];
		det *= ar[j];  /// end-hash

		int is;	 /// start-hash
		T d = T(1) / ar[j];
		if constexpr (rref) {
			for (int k = j; k < w; k++) {
				ar[k] *= d;
			}
			d = 1;
			is = 0;
		} else {
			is = r + 1;
		}  /// end-hash

		for (int i = is; i < h; i++) {	/// start-hash
			if (i == r) continue;
			auto& ai = a[i];
			if (!fz(ai[j])) {
				T e = ai[j] * d;
				for (int k = j; k < w; k++) {
					ai[k] -= ar[k] * e;
				}
			}
		}
		r++;
	}  /// end-hash
	return {r, det};
}

template <class T>
pair<Vec<T>, Vec<Vec<T>>> solve_lineareq(Vec<Vec<T>> a,
										 Vec<T> b,
										 F_better<T> fb,
										 F_zero<T> fz) {
	int h = int(a.size());
	assert(h);
	int w = int(a[0].size());
	for (int i = 0; i < h; i++) a[i].push_back(b[i]);  /// start-hash
	int r = sweep<true>(a, fb, fz, w).first;
	for (int i = r; i < h; i++) {
		if (!fz(a[i][w])) return {};
	}
	Vec<T> x(w);
	Vec<int> pivot(w, -1);
	int z = 0;
	for (int i = 0; i < r; i++) {
		while (fz(a[i][z])) z++;
		x[z] = a[i][w], pivot[z] = i;
	}  /// end-hash
	Vec<Vec<T>> ker;  /// start-hash
	for (int j = 0; j < w; j++) {
		if (pivot[j] == -1) {
			Vec<T> v(w);
			v[j] = 1;
			for (int k = 0; k < j; k++) {
				if (pivot[k] != -1) v[k] = -a[pivot[k]][j];
			}
			ker.push_back(v);
		}
	}  /// end-hash
	return {x, ker};
}

template <class T>
Vec<Vec<T>> mat_inv(Vec<Vec<T>> a,
					F_better<T> fb,
					F_zero<T> fz) {	 /// start-hash
	int n = int(a.size());
	Vec<Vec<T>> m(n, Vec<T>(2 * n));
	for (int i = 0; i < n; i++) {
		copy(begin(a[i]), end(a[i]), begin(m[i]));
		m[i][n + i] = 1;
	}
	if (sweep<true>(m, fb, fz, n).first != n) return {};
	Vec<Vec<T>> b(n);
	for (int i = 0; i < n; i++) {
		copy(begin(m[i]) + n, end(m[i]), back_inserter(b[i]));
	}
	return b;
}  /// end-hash

template <class T>
T mat_det(Vec<Vec<T>> a, F_better<T> fb, F_zero<T> fz) {  /// start-hash
	return sweep<false>(a, fb, fz).second;
}  /// end-hash

}  // namespace matrix