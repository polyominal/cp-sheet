#pragma once

/**
 * Description: Polygon operations
 * Source: Gifted infants library
 * Status: Tested with
 * - CGL_3_A (area2)
 * - CGL_3_C (contains)
 * - CGL_4_A (convex)
 * - CGL_4_B (diameter)
 * - CGL_4_C (convex_cut)
 */

#include "geometry/ccw.hpp"
#include "geometry/linear.hpp"

namespace geometry {

template <class T> T area2(const Vec<Point<T>>& pol) {	/// start-hash
	if (pol.empty()) return 0;
	T res = 0;
	auto a = pol.back();
	for (auto b : pol) {
		res += crs(a, b);
		a = b;
	}
	return res;
}  /// end-hash

// (1:left) | (2: right) is inside between v[i] -- v[i + 1]
template <class T>
Vec<pair<Point<T>, int>> insPolL(const Vec<Point<T>>& pol, const L<T>& l) {
	using Pi = pair<Point<T>, int>;
	Vec<Pi> v;
	Point<T> a, b = pol.back();
	for (auto c : pol) {
		a = b;
		b = c;
		Point<T> p;
		if (crossLL({a, b}, l, p) != 1) continue;
		int sa = ccw(l, a) % 2, sb = ccw(l, b) % 2;
		if (sa > sb) swap(sa, sb);
		if (sa != 1 && sb == 1) v.push_back({p, 1});
		if (sa == -1 && sb != -1) v.push_back({p, 2});
	}
	sort(begin(v), end(v), [&](Pi x, Pi y) {
		auto vl = vec(l);
		return dot(vl, x.first - l.s) < dot(vl, y.first - l.s);
	});
	int m = int(size(v));
	Vec<Pi> res;
	for (int i = 0; i < m; i++) {
		if (i) v[i].second ^= v[i - 1].second;
		if (!res.empty() && res.back().first == v[i].first) res.pop_back();
		res.push_back(v[i]);
	}
	return res;
}

// 0: outside, 1: on line, 2: inside
template <class T>
int contains(const Vec<Point<T>>& pol,
			 const Point<T>& p) {  /// start-hash
	if (pol.empty()) return 0;
	int in = -1;
	Point<T> a_, b_ = pol.back();
	for (auto c : pol) {
		a_ = b_, b_ = c;
		Point<T> a = a_, b = b_;
		if (ccw(a, b, p) == 0) return 1;
		if (a.y > b.y) swap(a, b);
		if (!(a.y <= p.y && p.y < b.y)) continue;
		if (sgn(a.y, p.y) ? (crs(a - p, b - p) > 0) : (a.x > p.x)) in *= -1;
	}
	return in + 1;
}  /// end-hash

// pol: sorted and distinct
template <class T>
Vec<Point<T>> convex_lower(const Vec<Point<T>>& pts) {	/// start-hash
	assert(size(pts) >= 2);
	Vec<Point<T>> res;
	for (auto d : pts) {
		while (size(res) > 1) {
			//if (ccw(res.end()[-2], res.end()[-1], d) != -1) break;
			if (ccw(res.end()[-2], res.end()[-1], d) == 1) break;
			res.pop_back();
		}
		res.push_back(d);
	}
	return res;
}  /// end-hash

template <class T> Vec<Point<T>> convex(Vec<Point<T>> pts) {  /// start-hash
	sort(begin(pts), end(pts));
	pts.erase(unique(begin(pts), end(pts)), end(pts));
	if (size(pts) <= 1) return pts;
	Vec<Point<T>> lo = convex_lower(pts);
	reverse(begin(pts), end(pts));
	Vec<Point<T>> up = convex_lower(pts);
	lo.insert(begin(lo), begin(up) + 1, end(up) - 1);
	return lo;
}  /// end-hash

template <class T>
Vec<Point<T>> convex_cut(const Vec<Point<T>>& pol,
						 const L<T>& l) {  /// start-hash
	if (pol.empty()) return {};
	Vec<Point<T>> q;
	Point<T> a, b = pol.back();
	for (auto c : pol) {
		a = b, b = c;
		if ((ccw(l, a) % 2) * (ccw(l, b) % 2) < 0) {
			Point<T> buf;
			crossLL(l, L(a, b), buf);
			q.push_back(buf);
		}
		if (ccw(l, b) != -1) q.push_back(b);
	}
	return q;
}  /// end-hash

// pol: convex; this calls f(a, b) for each candidate (a, b)
template <class T, class F>
void diameter(const Vec<Point<T>> pol, F f) {  /// start-hash
	int n = int(size(pol));
	if (n == 2) {
		f(pol[0], pol[1]);
		return;
	}
	int x = 0, y = 0;
	for (int i = 1; i < n; i++) {
		if (pol[i] < pol[x]) x = i;
		if (pol[y] < pol[i]) y = i;
	}
	int sx = x, sy = y;
	while (sx != y || sy != x) {
		f(pol[x], pol[y]);
		int nx = (x + 1 < n) ? x + 1 : 0, ny = (y + 1 < n) ? y + 1 : 0;
		if (crs(pol[nx] - pol[x], pol[ny] - pol[y]) < 0) {
			x = nx;
		} else {
			y = ny;
		}
	}
}  /// end-hash

}  // namespace geometry