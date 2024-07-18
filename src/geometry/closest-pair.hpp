#pragma once

/**
 * Description: Given a set of points, returns the
 * squared distance between the closest pair(s)
 * Source: https://github.com/anroysko/lETHargy-ctl/blob/main/content/geometry/closest-pair.cpp
 * Status: Tested with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_5_A
 * Time: O(N \log^2 N) but practically fast
 */

#include "contest/base.hpp"

namespace closest_pair_impl {

template <class T> using P = pair<T, T>;

template <class T> inline tuple<T, P<T>, P<T>> closest_pair(Vec<P<T>> pts) {
	assert(size(pts) >= 2);
	std::ranges::sort(pts, [](const auto& a, const auto& b) -> bool {
		return a.first < b.first;
	});
	using R = tuple<T, P<T>, P<T>>;
	auto sq = [&](T a) -> T {
		return a*a;
	};
	auto dist2 = [&](const auto& a, const auto& b) -> T {
		return sq(a.first-b.first) + sq(a.second-b.second);
	};
	auto best = R(dist2(pts[0], pts[1]), pts[0], pts[1]);
	auto rec = [&](auto self, int l, int r) -> void {
		if (l+1 == r) return;
		int m = (l+r)/2;
		self(self, l, m), self(self, m, r);

		auto cnds = Vec<P<T>>();
		for (int i = l; i < r; i++) {
			T dx = (pts[i].first - pts[m-1].first);
			if (dx * dx <= get<0>(best)) cnds.push_back(pts[i]);
		}
		std::ranges::sort(cnds, [](const auto& a, const auto& b) -> bool {
			return a.second < b.second;
		});
		int nc = int(size(cnds));
		for (int i = 0; i < nc; i++) {
			for (int j = i+1; j < i+7 && j < nc; j++) {
				best = min(best, R(dist2(cnds[i], cnds[j]), cnds[i], cnds[j]));
			}
		}
	};
	rec(rec, 0, int(size(pts)));
	return best;
}

} // namespace closest_pair_impl