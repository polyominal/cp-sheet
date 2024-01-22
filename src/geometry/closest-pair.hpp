/**
 * Description: Given a set of points, returns the
 * squared distance between the closest pair(s)
 * Source: https://github.com/anroysko/lETHargy-ctl/blob/main/content/geometry/closest-pair.cpp
 * Status: Tested with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_5_A
 * Time: O(N \log^2 N) but practically fast
 */

#pragma once

#include "geometry/base.hpp"

namespace geometry {

inline D closest_pair(V<P> pts) { /// start-hash
	assert(pts.size() > 1);
	sort(pts.begin(), pts.end(), [](const P& a, const P& b) -> bool {
		return a.x < b.x;
	});
	D best = dist2(pts[0] - pts[1]);
	yc([&](auto self, int l, int r) -> void {
		if (l+1 == r) return;
		int md = (l+r)/2;
		self(l, md), self(md, r);
		V<P> cnds;
		for (int i = l; i < r; i++) {
			D dx = (pts[i] - pts[md-1]).x;
			if (sgn(dx * dx, best) <= 0) cnds.push_back(pts[i]);
		}
		sort(cnds.begin(), cnds.end(), [](const P& a, const P& b) -> bool {
			return a.y < b.y;
		});
		int nc = int(cnds.size());
		for (int i = 0; i < nc; i++) {
			for (int j = i+1; j < i+7 && j < nc; j++) {
				best = min(best, dist2(cnds[i] - cnds[j]));
			}
		}
	})(0, int(pts.size()));
	return best;
} /// end-hash

} // namespace geometry
