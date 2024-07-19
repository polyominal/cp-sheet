#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2024-01-12
 * Description: Computes $\lfloor {a^{1/k}} \rfloor$
 * Status: Tested with https://judge.yosupo.jp/problem/kth_root_integer
 */

#include "contest/base.hpp"

template <class I = u64> I int_kth_root(I a, I k) {
	if (k == 1) return a;
	if (k >= 64) return (a == 0 ? 0 : 1);

	using T = __uint128_t;
	auto works = [&](T x) -> bool {
		T r = 1;
		for (int n = int(k); n; n >>= 1) {
			if (n & 1) r *= x;
			x *= x;
		}
		return r <= a;
	};
	if (a == I(-1)) a--;
	I rt = I(pow(double(a), nextafter(1 / double(k), 0)));
	while (works(rt + 1)) rt++;
	return rt;
}