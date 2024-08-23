#pragma once

/**
 * Description: Given a set of points, returns an arbitrary closest pair of points.
 * Source: https://judge.yosupo.jp/submission/214022
 * Status: Tested with https://judge.yosupo.jp/problem/closest_pair
 */

#include "contest/base.hpp"
#include "geometry/base.hpp"

namespace geometry {

template <class T> using P = Point<T>;

// PRECONDITION: There are at least 2 points
template <class T, class F> inline void closest_pair(Vec<P<T>> pts, F f) {
	int n = int(size(pts));
	using PT = P<T>;
	std::ranges::sort(pts, [](PT a, PT b) -> bool { return a.x < b.x; });
	T d = std::numeric_limits<T>::max();

	auto st = multiset<PT, decltype([](PT a, PT b) { return a.y < b.y; })>();
	auto its = Vec<typename decltype(st)::const_iterator>(size(pts));

	auto update = [&](PT a, PT b) {
		T d2 = dist2(a - b);
		if (d2 < d) {
			d = d2;
			f(a, b);
		}
	};

	for (int i = 0, j = 0; i < n; i++) {
		PT p = pts[i];

		auto sq = [](T x) { return x * x; };
		while (j < i && sq(p.x - pts[j].x) >= d) {
			st.erase(its[j++]);
		}
		auto u = st.upper_bound(p);
		{
			auto t = u;
			while (true) {
				if (t == begin(st)) break;
				t = prev(t);
				update(*t, p);
				if (sq(p.y - t->y) >= d) break;
			}
		}
		{
			auto t = u;
			while (true) {
				if (t == end(st)) break;
				if (sq(p.y - t->y) >= d) break;
				update(*t, p);
				t = next(t);
			}
		}
		its[i] = st.emplace_hint(u, p);
	}
}

}  // namespace geometry