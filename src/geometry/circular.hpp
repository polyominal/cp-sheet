#pragma once

/**
 * Description: Circle operations
 * Source: Gifted infants library
 * Status: Tested with
 * - CGL_7_A (insCC)
 * - CGL_7_B (incircle)
 * - CGL_7_C (outcircle)
 * - CGL_7_D (crossCL)
 */

#include "geometry/base.hpp"
#include "geometry/linear.hpp"

namespace geometry {

template <class T = double> struct C {
	using P = Point<T>;
	P c;
	T r;
	C(P c_ = P(), T r_ = T()) : c(c_), r(r_) {}

	friend P eval(const C& a, const double& angle) {
		return a.c + P::polar(a.r, angle);
	}
};

// NOT TESTED
// 0: outside; 1: on; 2: inside
template <class T> inline int contains(const C<T>& c, const Point<T>& p) {
	return sgn(c.r - dist(p - c.c)) + 1;
}

// 0-apart; 1-coincide;
// 2-a<b; 3-a<=b;
// 4-a>b; 5-a>=b;
// 6-a touches b; 7-a cross b
template <class T> inline int insCC(const C<T>& a, const C<T>& b) {
	T c = dist(a.c - b.c);	/// start-hash
	if (sgn(c) == 0 && sgn(a.r, b.r) == 0) return 1;
	int d = sgn(c + a.r - b.r);
	if (d <= 0) return d + 3;
	int e = sgn(c + b.r - a.r);
	if (e <= 0) return e + 5;
	int f = sgn(c - a.r - b.r);
	if (f <= 0) return -f + 6;
	return 0;  /// end-hash
}

template <class T>
inline C<T> incircle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
	T da = dist(b - c);	 /// start-hash
	T db = dist(a - c);
	T dc = dist(a - b);
	T s = da + db + dc;
	return C((a * da + b * db + c * dc) / s,
			 abs(crs(b - a, c - a)) / s);  /// end-hash
}

template <class T>
inline C<T> outcircle(const Point<T>& a, Point<T> b, Point<T> c) {
	b -= a, c -= a;	 /// start-hash
	T bb = dist2(b) / 2;
	T cc = dist2(c) / 2;
	T g = crs(b, c);
	T x = (bb * c.y - b.y * cc) / g;
	T y = (b.x * cc - bb * c.x) / g;
	T r = sqrt(x * x + y * y);
	x += a.x, y += a.y;
	return C(P(x, y), r);  /// end-hash
}

template <class T>
inline int crossCL(const C<T>& c, const L<T>& l, array<Point<T>, 2>& res) {
	T u = distLP(l, c.c);  /// start-hash
	int t = sgn(u, c.r);
	if (t == 1) return 0;
	Point<T> v = project(l, c.c);
	Point<T> d = (t == 0 ? Point<T>(0, 0)
						 : vec(l) * (sqrt(c.r * c.r - u * u) / dist(l)));
	res = {v - d, v + d};
	return 1 - t;  /// end-hash
}

// args of two intersections r, l seen by a.c,
// assuming two circles cross
template <class T>
inline pair<T, T> crossCC_args(const C<T>& a, const C<T>& b) {
	Point<T> diff = b.c - a.c;	/// start-hash
	T c = arg(diff);
	T d = arg(a.r, dist(diff), b.r);
	return {c - d, c + d};	/// end-hash
}

template <class T>
inline int crossCC(const C<T>& a, const C<T>& b, array<Point<T>, 2>& res) {
	int t = insCC(a, b);  /// start-hash
	if (t == 0 || t == 1 || t == 2 || t == 4) return 0;
	auto [l, r] = crossCC_args(a, b);
	res = {eval(a, l), eval(a, r)};
	return 2 - (t == 3 || t == 5 || t == 6);  /// end-hash
}

template <class T>
inline int tangent(const C<T>& c, const Point<T>& p, array<Point<T>, 2>& res) {
	Point<T> diff = p - c.c;  /// start-hash
	T dd = dist(diff);
	int t = sgn(c.r, dd);
	if (t == 1) return 0;
	T d = acos(min<T>(c.r / dd, 1));
	T a = arg(diff);
	res = {eval(c, a - d), eval(c, a + d)};
	return 1 - t;  /// end-hash
}

}  // namespace geometry