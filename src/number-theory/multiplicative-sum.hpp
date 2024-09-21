#pragma once

/**
 * Date: 2024-09-21
 * Source: https://judge.yosupo.jp/submission/110133
 */

#include "contest/base.hpp"

namespace multiplicative_sum {

using std::sqrt, std::cbrt;

inline i64 isqrt(i64 n) { return i64(sqrt(n)); }
inline i64 icbrt(i64 n) { return i64(cbrt(n)); }
inline i64 sq(i64 a) { return a * a; }

template <class T, int K> struct CountingPrime {
	using A = array<T, K>;	/// start-hash
	void add(A& a, const A& b) {
		for (int k = 0; k < K; k++) a[k] += b[k];
	}
	void sub(A& a, const A& b) {
		for (int k = 0; k < K; k++) a[k] -= b[k];
	}
	const Vec<int>& ps;
	const i64 n;
	const int n2, n3, n6;
	int s;
	Vec<i64> vs;
	Vec<A> sum, fw;
	A pref;	 /// end-hash

	A getpows(T p) {  /// start-hash
		A res;
		res[0] = 1;
		for (int k = 1; k < K; k++) {
			res[k] = res[k - 1] * p;
		}
		return res;
	}  /// end-hash

	void trans(int i, int p) {	/// start-hash
		A w = getpows(p);
		int j = get_idx(vs[i] / p);
		for (int k = 0; k < K; k++) {
			sum[i][k] -= (sum[j][k] - pref[k]) * w[k];
		}
	}  /// end-hash

	void trans2(int i, int p) {	 /// start-hash
		A w = getpows(p);
		int j = get_idx(vs[i] / p);
		A z = sum[j];
		if (j >= n3) {
			j -= n3;
			for (; j < int(fw.size()); j += (j + 1) & (-j - 1)) {
				add(z, fw[j]);
			}
		}
		for (int k = 0; k < K; k++) {
			sum[i][k] -= (z[k] - pref[k]) * w[k];
		}
	}  /// end-hash

	void upd(int i, i64 cur, bool f) {	/// start-hash
		if (!f) {
			A w = getpows(cur);
			for (int j = get_idx(cur) - n3; j >= 0; j -= (j + 1) & (-j - 1)) {
				sub(fw[j], w);
			}
		}
		for (int j = i; cur * ps[j] <= vs[n3]; j++) {
			upd(j, cur * ps[j], false);
		}
	}  /// end-hash

	CountingPrime(i64 n_, const Vec<int>& ps_, std::function<T(int, i64)> sump)
		: ps(ps_),
		  n(n_),
		  n2(int(isqrt(n))),
		  n3(int(icbrt(n))),
		  n6(int(icbrt(n2))) {	/// start-hash
		{
			i64 v = n;
			while (v) {
				vs.push_back(v);
				v = n / (n / v + 1);
			}
		}
		s = int(vs.size());

		sum.resize(s);
		for (int i = 0; i < s; i++) {
			for (int k = 0; k < K; k++) {
				sum[i][k] = sump(k, vs[i]) - 1;
			}
		}

		int idx = 0;
		{
			while (ps[idx] <= n6) {
				for (int i = 0; i < s; i++) {
					if (sq(ps[idx]) > vs[i]) break;
					trans(i, ps[idx]);
				}
				add(pref, getpows(ps[idx]));
				idx++;
			}
		}
		{
			fw.resize(s - n3);
			while (ps[idx] <= n3) {
				for (int i = 0; i < n3; i++) {
					if (sq(ps[idx]) > vs[i]) break;
					trans2(i, ps[idx]);
				}
				upd(idx, ps[idx], true);
				add(pref, getpows(ps[idx]));
				idx++;
			}
			for (int i = s - n3 - 1; i >= 0; i--) {
				int j = i + ((i + 1) & (-i - 1));
				if (j < int(fw.size())) {
					add(fw[i], fw[j]);
				}
			}
			for (int i = 0; i < s - n3; i++) {
				add(sum[i + n3], fw[i]);
			}
		}
		{
			while (ps[idx] <= n2) {
				for (int i = 0; i < s; i++) {
					if (sq(ps[idx]) > vs[i]) break;
					trans(i, ps[idx]);
				}
				add(pref, getpows(ps[idx]));
				idx++;
			}
		}
	}  /// end-hash

	int get_idx(i64 a) {  /// start-hash
		return int(a <= n2 ? s - a : n / a - 1);
	}  /// end-hash

	Vec<T> buf;
	T multiplicative_sum(const array<T, K>& coeff,
						 std::function<T(i64, int, int)> f) {  /// start-hash
		// sum of [p is prime] f(p)
		buf.resize(s);
		for (int i = 0; i < s; i++) {
			buf[i] = std::inner_product(begin(sum[i]), end(sum[i]),
										begin(coeff), T(0));
		}

		T ans = 1 + buf[0];
		auto dfs = [&](auto self, int i, int c, i64 v, i64 lim, T cur) -> void {
			ans += cur * f(v * ps[i], ps[i], c + 1);
			if (lim >= sq(ps[i])) {
				self(self, i, c + 1, v * ps[i], lim / ps[i], cur);
			}
			cur *= f(v, ps[i], c);
			ans += cur * (buf[get_idx(lim)] - buf[get_idx(ps[i])]);
			for (int j = i + 1; sq(ps[j]) <= lim; j++) {
				self(self, j, 1, ps[j], lim / ps[j], cur);
			}
		};
		for (int i = 0; true; i++) {
			if (sq(ps[i]) <= n) {
				dfs(dfs, i, 1, ps[i], n / ps[i], 1);
			} else {
				break;
			}
		}
		return ans;
	}  /// end-hash
};

template <class T> T get_totient_sum(i64 n, const Vec<int>& primes) {
	auto cp = CountingPrime<T, 2>(n, primes, [&](int k, i64 l) -> T {
		if (k == 0) {
			return T(l);
		} else if (k == 1) {
			if (l % 2 == 0) {
				return T(l / 2) * T(l + 1);
			} else {
				return T(l) * T((l + 1) / 2);
			}
		} else {
			assert(false);
		}
	});
	return cp.multiplicative_sum({-T(1), T(1)}, [](i64, int p, int c) -> T {
		auto res = T(p - 1);
		for (int i = 1; i < c; i++) {
			res *= T(p);
		}
		return res;
	});
}

}  // namespace multiplicative_sum