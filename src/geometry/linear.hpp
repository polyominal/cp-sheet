/**
 * Description: Line/segment operations
 * Source: Gifted Infants library
 * Status: Tested with
 * - CGL_1_A (projection)
 * - CGL_1_B (projection)
 * - CGL_2_A (L::vec)
 * - CGL_2_B (insSS)
 * - CGL_2_C (crossSS, crossLL)
 */

#pragma once

#include "geometry/ccw.hpp"

namespace geometry {

// Work in progress
struct L { /// start-hash
	P s, t;
	L(P s_ = P(), P t_ = P()) : s(s_), t(t_) {}
	friend P vec(const L& l) { return l.t - l.s; }
	friend auto dist(const L& l) { return dist(vec(l)); }
	friend D arg(const L& l) { return arg(vec(l)); }
}; /// end-hash

inline P project(const L& l, const P& p) { /// start-hash
	P v = vec(l);
	return l.s + v * dot(v, p - l.s) / dist2(v);
} /// end-hash

inline int ccw(const L& l, const P& p) { return ccw(l.s, l.t, p); }

inline bool insSL(const L& s, const L& l) { /// start-hash
	int a = ccw(l, s.s), b = ccw(l, s.t);
	return (a % 2 == 0 || b % 2 == 0 || a != b);
} /// end-hash

inline bool insSS(const L& s, const L& t) { /// start-hash
	int a = ccw(s, t.s), b = ccw(s, t.t),
		c = ccw(t, s.s), d = ccw(t, s.t);
	return (a * b <= 0 && c * d <= 0);
} /// end-hash

inline D distLP(const L& l, const P& p) { /// start-hash
	return std::abs(crs(vec(l), p - l.s)) / dist(l);
} /// end-hash

inline D distSP(const L& s, const P& p) { /// start-hash
	P q = project(s, p);
	if (ccw(s, q) == 0) {
		return dist(p - q);
	} else {
		return min(dist(s.s - p), dist(s.t - p));
	}
} /// end-hash

inline D distSS(const L& s, const L& t) { /// start-hash
	if (insSS(s, t)) return 0;
	return min({
		distSP(s, t.s), distSP(s, t.t), distSP(t, s.s), distSP(t, s.t)
	});
} /// end-hash

// TODO: usage
inline int crossLL(const L& l, const L& m, P& r) { /// start-hash
	P vl = vec(l), vm = vec(m);
	D cr1 = crs(vl, vm), cr2 = crs(vl, l.t - m.s);
	if (sgncrs(vl, vm) == 0) {
		r = l.s;
		if (sgncrs(vec(l), l.t - m.s)) return 0;
		return -1;
	}
	r = m.s + vm * cr2 / cr1;
	return 1;
} /// end-hash

// TODO usage
inline int crossSS(const L& l, const L& m, P& r) { /// start-hash
	int u = crossLL(l, m, r);
	if (u == 0) return 0;
	if (u == -1) {
		r = max(min(l.s, l.t), min(m.s, m.t));
		P q = min(max(l.s, l.t), max(m.s, m.t));
		return (q < r) ? 0 : (q == r ? 1 : -1);
	}
	if (ccw(l, r) == 0 && ccw(m, r) == 0) return 1;
	return 0;
} /// end-hash

} // namespace geometry