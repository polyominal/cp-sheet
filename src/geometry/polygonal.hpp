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

#pragma once

#include "geometry/ccw.hpp"
#include "geometry/linear.hpp"

namespace geometry {

inline D area2(const V<P>& pol) { /// start-hash
	if (pol.empty()) return 0;
	D res = 0;
	P a = pol.back();
	for (P b : pol) {
		res += crs(a, b);
		a = b;
	}
	return res;
} /// end-hash

// (1:left) | (2: right) is inside between v[i] -- v[i + 1]
inline V<pair<P, int>> insPolL(const V<P>& pol, const L& l) {
	using Pi = pair<P, int>;
	V<Pi> v;
	P a, b = pol.back();
	for (auto c: pol) {
		a = b; b = c;
		P p;
		if (crossLL({a, b}, l, p) != 1) continue;
		int sa = ccw(l, a) % 2, sb = ccw(l, b) % 2;
		if (sa > sb) swap(sa, sb);
		if (sa != 1 && sb == 1) v.push_back({p, 1});
		if (sa == -1 && sb != -1) v.push_back({p, 2});
	}
	sort(v.begin(), v.end(), [&](Pi x, Pi y){
		auto vl = vec(l);
		return dot(vl, x.first - l.s) < dot(vl, y.first - l.s);
	});
	int m = int(v.size());
	V<Pi> res;
	for (int i = 0; i < m; i++) {
		if (i) v[i].second ^= v[i - 1].second;
		if (!res.empty() && res.back().first == v[i].first) res.pop_back();
		res.push_back(v[i]);
	}
	return res;
}

// 0: outside, 1: on line, 2: inside
inline int contains(const V<P>& pol, const P& p) { /// start-hash
	if (!pol.size()) return 0;
	int in = -1;
	P a_, b_ = pol.back();
	for (auto c : pol) {
		a_ = b_, b_ = c;
		P a = a_, b = b_;
		if (ccw(a, b, p) == 0) return 1;
		if (a.y > b.y) swap(a, b);
		if (!(a.y <= p.y && p.y < b.y)) continue;
		if (sgn(a.y, p.y) ? (crs(a - p, b - p) > 0) : (a.x > p.x)) in *= -1;
	}
	return in + 1;
} /// end-hash

// pol: sorted and distinct
inline V<P> convex_lower(const V<P>& pts) { /// start-hash
	assert(pts.size() >= 2);
	V<P> res;
	for (P d : pts) {
		while (res.size() > 1) {
			//if (ccw(res.end()[-2], res.end()[-1], d) != -1) break;
			if (ccw(res.end()[-2], res.end()[-1], d) == 1) break;
			res.pop_back();
		}
		res.push_back(d);
	}
	return res;
} /// end-hash

inline V<P> convex(V<P> pts) { /// start-hash
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	if (pts.size() <= 1) return pts;
	V<P> lo = convex_lower(pts);
	reverse(pts.begin(), pts.end());
	V<P> up = convex_lower(pts);
	lo.insert(lo.begin(), up.begin() + 1, up.end() - 1);
	return lo;
} /// end-hash

inline V<P> convex_cut(const V<P>& pol, const L& l) { /// start-hash
	if (pol.empty()) return {};
	V<P> q;
	P a, b = pol.back();
	for (auto c : pol) {
		a = b, b = c;
		if ((ccw(l, a) % 2) * (ccw(l, b) % 2) < 0) {
			P buf;
			crossLL(l, L(a, b), buf);
			q.push_back(buf);
		}
		if (ccw(l, b) != -1) q.push_back(b);
	}
	return q;
} /// end-hash

// pol: convex
inline D diameter(const V<P>& pol) { /// start-hash
	int n = int(pol.size());
	if (n == 2) return dist(pol[1] - pol[0]);
	int x = 0, y = 0;
	for (int i = 1; i < n; i++) {
		if (pol[i] < pol[x]) x = i;
		if (pol[y] < pol[i]) y = i;
	}
	D ans = 0;
	int sx = x, sy = y;
	while (sx != y || sy != x) {
		ans = max(ans, dist(pol[x] - pol[y]));
		int nx = (x + 1 < n) ? x + 1 : 0, ny = (y + 1 < n) ? y + 1 : 0;
		if (crs(pol[nx] - pol[x], pol[ny] - pol[y]) < 0) {
			x = nx;
		} else {
			y = ny;
		}
	}
	return ans;
} /// end-hash

} // namespace geometry