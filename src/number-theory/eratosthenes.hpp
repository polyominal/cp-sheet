/**
 * Author: Nyaan on Codeforces
 * Date: 2023-09-09
 * Source: https://nyaannyaan.github.io/library/prime/prime-enumerate.hpp
 * Description: Prime sieve for generating all primes up to a certain limit $n$
 * Status: Good luck
 */

#pragma once

#include "contest/base.hpp"

inline Vec<int> prime_enumerate(int n) {
	Vec<bool> sieve(n/3+1, true); /// start-hash
	int qe = int(sieve.size());
	int n2 = int(sqrt(n));
	for (int p = 5, d = 4, i = 1; p <= n2; p += d = 6-d, i++) {
		if (!sieve[i]) continue;
		for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2*p; q < qe; q += r = s-r) {
			sieve[q] = false;
		}
	} /// end-hash
	Vec<int> res{2, 3}; /// start-hash
	for (int p = 5, d = 4, i = 1; p <= n; p += d = 6-d, i++) {
		if (sieve[i]) res.push_back(p);
	}
	while (!res.empty() && res.back() > n) res.pop_back();
	return res; /// end-hash
}