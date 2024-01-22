/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form $y = kx+m$,
 * and query maximum values at given points.
 * Useful for dynamic programming (``convex hull trick'')
 * Time: O(\log N) with a large constant factor
 * Status: Tested
 */

#pragma once

#include "contest/base.hpp"

namespace line_container {

struct Line { /// start-hash
	mutable ll k, m, p;
	bool operator < (const Line& o) const { return k < o.k; }
	bool operator < (ll x) const { return p < x; }
}; /// end-hash

struct LineContainer : multiset<Line, less<>> {
	using I = iterator; /// start-hash
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = numeric_limits<ll>::max();
	static ll div(ll a, ll b) {
		return a / b - ((a ^ b) < 0 && a % b);
	} /// end-hash
	bool isect(I x, I y) { /// start-hash
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	} /// end-hash
	void add(ll k, ll m) { /// start-hash
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) {
			isect(x, y = erase(y));
		}
		while ((y = x) != begin() && (--x)->p >= y->p) {
			isect(x, erase(y));
		}
	} /// end-hash
	ll query(ll x) { /// start-hash
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	} /// end-hash
};

} // namespace line_container