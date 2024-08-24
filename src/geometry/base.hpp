#pragma once

/**
 * Description: Primitive operations
 * Source: Gifted Infants library
 * Status: Good luck
 */

#include "contest/base.hpp"

namespace geometry {

using std::fmod;

const double EPS = 1e-9;
template <class T> inline int sgn(T a) { return (a > EPS) - (a < -EPS); }
template <class T> inline int sgn(T a, T b) { return sgn(a - b); }

const double PI = acos(-1.);

template <class T> struct Point {
	using P = Point;
	T x, y;
	Point(T x_ = T(), T y_ = T()) : x(x_), y(y_) {}

	P& operator+=(const P& p) {	 /// start-hash
		x += p.x, y += p.y;
		return *this;
	}
	P& operator-=(const P& p) {
		x -= p.x, y -= p.y;
		return *this;
	}
	friend P operator+(const P& a, const P& b) { return P(a) += b; }
	friend P operator-(const P& a, const P& b) {
		return P(a) -= b;
	}  /// end-hash

	P& operator*=(const T& t) {	 /// start-hash
		x *= t, y *= t;
		return *this;
	}
	P& operator/=(const T& t) {
		x /= t, y /= t;
		return *this;
	}
	friend P operator*(const P& a, const T& t) { return P(a) *= t; }
	friend P operator/(const P& a, const T& t) {
		return P(a) /= t;
	}  /// end-hash

	friend T dot(const P& a, const P& b) { return a.x * b.x + a.y * b.y; }
	friend T crs(const P& a, const P& b) { return a.x * b.y - a.y * b.x; }

	P operator-() const { return P(-x, -y); }

	friend int cmp(const P& a, const P& b) {  /// start-hash
		int z = sgn(a.x, b.x);
		return z ? z : sgn(a.y, b.y);
	}  /// end-hash

	friend bool operator<(const P& a, const P& b) { return cmp(a, b) < 0; }
	friend bool operator<=(const P& a, const P& b) { return cmp(a, b) <= 0; }

	friend T dist2(const P& p) { return p.x * p.x + p.y * p.y; }
	friend auto dist(const P& p) { return sqrt(D(dist2(p))); }

	friend P unit(const P& p) { return p / p.dist(); }

	friend double arg(const P& p) { return atan2(p.y, p.x); }

	friend T rabs(const P& p) { return max(abs(p.x), abs(p.y)); }

	friend bool operator==(const P& a, const P& b) {
		return sgn(rabs(a - b)) == 0;
	}
	friend bool operator!=(const P& a, const P& b) { return !(a == b); }

	explicit operator pair<T, T>() const { return pair<T, T>(x, y); }

	static P polar(double m, double a) { return P(m * cos(a), m * sin(a)); }
};
template <class T>
int sgncrs(const Point<T>& a, const Point<T>& b) {	/// start-hash
	T cr = crs(a, b);
	if (abs(cr) <= (rabs(a) + rabs(b)) * EPS) return 0;
	return (cr < 0 ? -1 : 1);
}  /// end-hash

// not tested
template <class D> D norm_angle(D a) {	/// start-hash
	D res = fmod(a + PI, 2 * PI);
	if (res < 0) {
		res += PI;
	} else {
		res -= PI;
	}
	return res;
}  /// end-hash

// not tested
template <class D> D norm_nonnegative(D a) {  /// start-hash
	D res = fmod(a, 2 * PI);
	if (res < 0) res += 2 * PI;
	return res;
}  /// end-hash

// arg given lengths a, b, c,
// assumming a, b, c are valid
template <class D> D arg(D a, D b, D c) {  /// start-hash
	return acos(std::clamp<D>((a * a + b * b - c * c) / (2 * a * b), -1, 1));
}  /// end-hash

}  // namespace geometry