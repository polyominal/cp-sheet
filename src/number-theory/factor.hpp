/**
 * Author: Hanfei Chen
 * Date: 2024-01-16
 * Description: Returns prime
 * factors in ascending order (e.g. 2299 -> \{11, 11, 19\})
 * Source: https://miller-rabin.appspot.com/
 * Time: O(n^{1/4})
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/factorize (factorize)
 * - https://judge.yosupo.jp/problem/primitive_root (primitive_root)
 * - https://judge.yosupo.jp/problem/mul_modp_convolution (primitive_root)
 */

#pragma once

#include "contest/extra.hpp"
#include <random>

namespace factor {

template <class T> T pow_mod(T a, u64 b, T m) { /// start-hash
	T r = 1;
	while (b) {
		if (b & 1) r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return r;
} /// end-hash

template <class T> bool is_prime(T n) { /// start-hash
	if (n <= 1 || n % 2 == 0) return (n == 2);
	int s = __builtin_ctzll(n-1);
	T d = (n-1) >> s;
	for (u128 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		a %= n;
		if (a == 0) continue;
		a = pow_mod<u128>(a, d, n);
		if (T(a) == 1 || T(a) == n-1) continue;
		for (int i = 0; i < s-1; i++) {
			a = a * a % n;
			if (T(a) == n-1) break;
		}
		if (T(a) != n-1) return false;
	}
	return true;
} /// end-hash

// Fake pollard-rho, which does not guarantee
// to return a nontrivial divisor of n
template <class T> T pollard(T n) {
	assert(n >= 2);
	if (n % 2 == 0) return 2;
	static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	T c = uniform_int_distribution<T>(1, n-1)(rng);
	T y = uniform_int_distribution<T>(1, n-1)(rng);
	auto f = [&](T a) -> T { /// start-hash
		return T((u128(a) * a + c) % n);
	};
	for (int s = 1; ; s *= 2) {
		T x = y, d = 1;
		for (int i = 0; i < s; i++) y = f(y);
		static constexpr int block = 256;
		for (int i = 0; i < s; i += block) {
			T yb = y;
			for (int j = 0; j < block && j < s-i; j++) {
				y = f(y);
				d = T(u128(d) * (y-x+n) % n);
			}
			d = __gcd(n, d);
			if (d == 1) continue;
			if (d == n) {
				for (d = 1, y = yb; d == 1; ) {
					y = f(y);
					d = __gcd(n, y-x+n);
				}
			}
			return d;
		}
	} /// end-hash
}

// Returns prime factors in ascending order
template <class T> V<T> factorize(T n) { /// start-hash
	if (n == 1) return {};
	if (is_prime(n)) return {n};
	T f = pollard(n);
	auto a = factorize(f), b = factorize(n / f);
	V<T> c(a.size() + b.size());
	merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
	return c;
} /// end-hash

template <class T> T primitive_root(T p) {
	assert(is_prime(p));
	auto f = factorize(p-1);
	while (true) {
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
		T c = uniform_int_distribution<T>(1, p-1)(rng);
		if ([&]() -> bool { /// start-hash
			for (T d : f) {
				if (pow_mod<u128>(c, (p-1) / d, p) == 1) return false;
			}
			return true;
		}()) return c; /// end-hash
	}
}

} // namespace factor