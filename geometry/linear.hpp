#pragma once

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

#include "geometry/ccw.hpp"

namespace geometry {

// Work in progress
template <class T> struct L {
	using P = Point<T>;	 /// start-hash
	P s, t;
	L(P s_ = P(), P t_ = P()) : s(s_), t(t_) {}
	friend P vec(const L& l) { return l.t - l.s; }
	friend auto dist(const L& l) { return dist(vec(l)); }
	friend double arg(const L& l) { return arg(vec(l)); }  /// end-hash
};

template <class T> Point<T> project(const L<T>& l, const Point<T>& p) {
	Point<T> v = vec(l);						  /// start-hash
	return l.s + v * dot(v, p - l.s) / dist2(v);  /// end-hash
}

template <class T> int ccw(const L<T>& l, const Point<T>& p) {
	return ccw(l.s, l.t, p);
}

template <class T> bool insSL(const L<T>& s, const L<T>& l) {
	int a = ccw(l, s.s), b = ccw(l, s.t);		  /// start-hash
	return (a % 2 == 0 || b % 2 == 0 || a != b);  /// end-hash
}

template <class T> bool insSS(const L<T>& s, const L<T>& t) {
	int a = ccw(s, t.s), b = ccw(s, t.t), c = ccw(t, s.s),
		d = ccw(t, s.t);				/// start-hash
	return (a * b <= 0 && c * d <= 0);	/// end-hash
}

template <class T> double distLP(const L<T>& l, const Point<T>& p) {
	return abs(crs(vec(l), p - l.s)) / dist(l);
}  /// end-hash

template <class T> double distSP(const L<T>& s, const Point<T>& p) {
	Point<T> q = project(s, p);	 /// start-hash
	if (ccw(s, q) == 0) {
		return dist(p - q);
	} else {
		return min(dist(s.s - p), dist(s.t - p));
	}  /// end-hash
}

template <class T> double distSS(const L<T>& s, const L<T>& t) {
	if (insSS(s, t)) return 0;	/// start-hash
	return min({distSP(s, t.s), distSP(s, t.t), distSP(t, s.s),
				distSP(t, s.t)});  /// end-hash
}

// TODO: usage
template <class T> int crossLL(const L<T>& l, const L<T>& m, Point<T>& r) {
	Point<T> vl = vec(l), vm = vec(m);	/// start-hash
	T cr1 = crs(vl, vm), cr2 = crs(vl, l.t - m.s);
	if (sgncrs(vl, vm) == 0) {
		r = l.s;
		if (sgncrs(vec(l), l.t - m.s)) return 0;
		return -1;
	}
	r = m.s + vm * cr2 / cr1;
	return 1;  /// end-hash
}

// TODO usage
template <class T> int crossSS(const L<T>& l, const L<T>& m, Point<T>& r) {
	int u = crossLL(l, m, r);  /// start-hash
	if (u == 0) return 0;
	if (u == -1) {
		r = max(min(l.s, l.t), min(m.s, m.t));
		Point<T> q = min(max(l.s, l.t), max(m.s, m.t));
		return (q < r) ? 0 : (q == r ? 1 : -1);
	}
	if (ccw(l, r) == 0 && ccw(m, r) == 0) return 1;
	return 0;  /// end-hash
}

}  // namespace geometry