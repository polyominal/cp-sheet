#pragma once

/**
 * Date: 2024-09-13
 * Source: https://github.com/hos-lyric/libra/blob/a10f930a15bcc15db971ca5bd95a62bc65c55bb5/number/gojo.cpp
 */

#include "contest/base.hpp"

// y^f(0) x y^(f(1)-f(0)) x y^(f(2)-f(1)) x ... x y^(f(n)-f(n-1))
//   where f(i) = floor((a i + b) / m)
// S: (unsigned or signed) integer
//   (an + b) and (m + a) does not overflow
// T: monoid with pow
//   e: identity
template <class S, class M> M scary_prod(S n, S a, S b, S m, M e, M x, M y) {
	assert(n >= 0);
	assert(a >= 0);
	assert(b >= 0);
	assert(m >= 1);
	S c = (a * n + b) / m;	/// start-hash
	M p = e, s = e;
	while (true) {
		S u = a / m, v = b / m;
		a %= m, b %= m;
		x = x * y.pow(u);
		p = p * y.pow(v);
		c -= u * n + v;
		if (c == 0) break;
		S d = (m * c - b - 1) / a + 1;
		s = y * x.pow(n - d) * s;
		b = m - b - 1 + a, n = c - 1, c = d;
		swap(a, m), swap(x, y);
	}
	return p * x.pow(n) * s;  /// end-hash
}

// sum_{i=0, ..., n-1} floor((a i + b) / m)
// Set e = Sum(), x = Sum(1, 0, 0), y = Sum(0, 1, 0)
struct Sum {  /// start-hash
	i64 cnt, add, res;
	Sum(i64 a = 0, i64 b = 0, i64 c = 0) : cnt(a), add(b), res(c) {}
	Sum operator*(const Sum& o) const {
		return Sum(cnt + o.cnt, add + o.add, res + o.res + add * o.cnt);
	}
	Sum pow(i64 e) const {
		return Sum(e * cnt, e * add, e * res + e * (e - 1) / 2 * cnt * add);
	}
};	/// end-hash

// min_{i=0, ..., n-1} floor((a i + b) % m)
// Set e = MinMod(), x = MinMod(a, 0), y = MinMod(-m, INF)
struct MinMod {	 /// start-hash
	static constexpr i64 INF = 1e18;
	i64 sum;
	i64 best;
	MinMod(i64 a = 0, i64 b = INF) : sum(a), best(b) {}
	MinMod operator*(const MinMod& o) const {
		return MinMod(sum + o.sum, min(best, sum + o.best));
	}
	MinMod pow(i64 e) const {
		return e == 0 ? MinMod()
					  : MinMod(e * sum, (sum < 0 ? (e - 1) * sum : 0) + best);
	}
};	/// end-hash