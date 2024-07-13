/**
 * Description: Circle operations
 * Source: Gifted infants library
 * Status: Tested with
 * - CGL_7_A (insCC)
 * - CGL_7_B (incircle)
 * - CGL_7_C (outcircle)
 * - CGL_7_D (crossCL)
 */

#pragma once

#include "geometry/base.hpp"
#include "geometry/linear.hpp"

namespace geometry {

struct C {
	P c;
	D r;
	C(P c_ = P(), D r_ = D()) : c(c_), r(r_) {}

	friend P eval(const C& a, const D& angle) {
		return a.c + P::polar(a.r, angle);
	}
};

// NOT TESTED
// 0: outside; 1: on; 2: inside
inline int contains(const C& c, const P& p) {
	return sgn(c.r - dist(p - c.c)) + 1;
}

// 0-apart; 1-coincide;
// 2-a<b; 3-a<=b;
// 4-a>b; 5-a>=b;
// 6-a touches b; 7-a cross b
inline int insCC(const C& a, const C& b) {
	D c = dist(a.c - b.c); /// start-hash
	if (sgn(c) == 0 && sgn(a.r, b.r) == 0) return 1;
	int d = sgn(c + a.r - b.r);
	if (d <= 0) return d+3;
	int e = sgn(c + b.r - a.r);
	if (e <= 0) return e+5;
	int f = sgn(c - a.r - b.r);
	if (f <= 0) return -f+6;
	return 0; /// end-hash
}

inline C incircle(const P& a, const P& b, const P& c) {
	D da = dist(b - c); /// start-hash
	D db = dist(a - c);
	D dc = dist(a - b);
	D s = da + db + dc;
	return C(
		(a * da + b * db + c * dc) / s,
		abs(crs(b-a, c-a)) / s
	); /// end-hash
}

inline C outcircle(const P& a, P b, P c) {
	b -= a, c -= a; /// start-hash
	D bb = dist2(b) / 2;
	D cc = dist2(c) / 2;
	D g = crs(b, c);
	D x = (bb * c.y - b.y * cc) / g;
	D y = (b.x * cc - bb * c.x) / g;
	D r = sqrt(x * x + y * y);
	x += a.x, y += a.y;
	return C(P(x, y), r); /// end-hash
}

inline int crossCL(const C& c, const L& l, array<P, 2>& res) {
	D u = distLP(l, c.c); /// start-hash
	int t = sgn(u, c.r);
	if (t == 1) return 0;
	P v = project(l, c.c);
	P d = (t == 0 ? P(0, 0) : vec(l) * (sqrt(c.r * c.r - u * u) / dist(l)));
	res = {v - d, v + d};
	return 1 - t; /// end-hash
}

// args of two intersections r, l seen by a.c,
// assuming two circles cross
inline pair<D, D> crossCC_args(const C& a, const C& b) {
	P diff = b.c - a.c; /// start-hash
	D c = arg(diff);
	D d = arg(a.r, dist(diff), b.r);
	return {c - d, c + d}; /// end-hash
}

inline int crossCC(const C& a, const C& b, array<P, 2>& res) {
	int t = insCC(a, b); /// start-hash
	if (t == 0 || t == 1 || t == 2 || t == 4) return 0;
	auto [l, r] = crossCC_args(a, b);
	res = {eval(a, l), eval(a, r)};
	return 2 - (t == 3 || t == 5 || t == 6); /// end-hash
}

inline int tangent(const C& c, const P& p, array<P, 2>& res) {
	P diff = p - c.c; /// start-hash
	D dd = dist(diff);
	int t = sgn(c.r, dd);
	if (t == 1) return 0;
	D d = acos(min<D>(c.r / dd, 1));
	D a = arg(diff);
	res = {eval(c, a - d), eval(c, a + d)};
	return 1 - t; /// end-hash
}

} // namespace geometry