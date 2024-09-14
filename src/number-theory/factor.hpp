#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2024-01-16
 * Description: Returns prime
 * factors in ascending order (e.g. 2299 -> \{11, 11, 19\})
 * Source:
 * - https://miller-rabin.appspot.com/
 * - https://github.com/kth-competitive-programming/kactl/blob/5d1e141e617ff73643b4b1d57d8e6df5d70f902e/content/number-theory/Factor.h
 * Time: O(n^{1/4})
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/factorize (factorize)
 * - https://judge.yosupo.jp/problem/primitive_root (primitive_root)
 * - https://judge.yosupo.jp/problem/mul_modp_convolution (primitive_root)
 */

#include "contest/base.hpp"

namespace factor {

template <class T> T pow_mod(T a, u64 b, T m) {
	T r = 1;  /// start-hash
	while (b) {
		if (b & 1) r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return r;  /// end-hash
}

template <class T> bool is_prime(T n) {
	if (n <= 1 || n % 2 == 0) return (n == 2);	/// start-hash
	int s = __builtin_ctzll(n - 1);
	T d = (n - 1) >> s;
	for (u128 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		a %= n;
		if (a == 0) continue;
		a = pow_mod<u128>(a, d, n);
		if (T(a) == 1 || T(a) == n - 1) continue;
		for (int i = 0; i < s - 1; i++) {
			a = a * a % n;
			if (T(a) == n - 1) break;
		}
		if (T(a) != n - 1) return false;
	}
	return true;  /// end-hash
}

template <class T> T pollard(T n) {
	T x = 0, y = 0, t = 30, p = 2, it = 1;	/// start-hash
	auto f = [&](T a) { return T(u128(a) * a % n) + it; };
	while (t++ % 40 || std::gcd(p, n) == 1) {
		if (x == y) {
			x = ++it, y = f(x);
		}
		T d = max(x, y) - min(x, y);
		if (T q = T(u128(p) * d % n); q) {
			p = q;
		}
		x = f(x), y = f(f(y));
	}
	return std::gcd(p, n);	/// end-hash
}

// Returns prime factors in ascending order
template <class T> Vec<T> factorize(T n) {
	if (n == 1) return {};	/// start-hash
	if (is_prime(n)) return {n};
	T f = pollard(n);
	auto a = factorize(f), b = factorize(n / f);
	Vec<T> c(a.size() + b.size());
	merge(begin(a), end(a), begin(b), end(b), begin(c));
	return c;  /// end-hash
}

template <class T> T primitive_root(T p) {
	assert(is_prime(p));  /// start-hash
	auto f = factorize(p - 1);
	T c;
	while (true) {
		c = rand_int<T>(1, p - 1);
		if (!std::ranges::any_of(f, [&](T d) {
				return pow_mod<u128>(c, (p - 1) / d, p) == 1;
			})) {
			break;
		}
	}
	return c;  /// end-hash
}

}  // namespace factor