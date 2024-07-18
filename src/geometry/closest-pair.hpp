#pragma once

/**
 * Description: Given a set of points, returns an arbitrary closest pair of points.
 * Source: https://judge.yosupo.jp/submission/214022
 * Status: Tested with https://judge.yosupo.jp/problem/closest_pair
 */

#include "contest/base.hpp"

namespace closest_pair_impl {

template <class T> using P = pair<T, T>;

// PRECONDITION: There are at least 2 points
template <class T> inline tuple<T, P<T>, P<T>> closest_pair(Vec<P<T>> pts) {
	int n = int(size(pts));
	using PT = P<T>;
	std::ranges::sort(pts,
					  [](PT a, PT b) -> bool { return a.first < b.first; });
	auto sq = [&](T a) -> T { return a * a; };
	auto dist2 = [&](PT a, PT b) -> T {
		return sq(a.first - b.first) + sq(a.second - b.second);
	};

	T d = std::numeric_limits<T>::max();
	PT pa, pb;
	auto update = [&](PT a, PT b) {
		auto nd = dist2(a, b);
		if (nd < d) {
			d = nd, pa = a, pb = b;
		}
	};

	auto st =
		multiset<PT,
				 decltype([](PT a, PT b) { return a.second < b.second; })>();
	auto its = Vec<typename decltype(st)::const_iterator>(size(pts));

	for (int i = 0, f = 0; i < n; i++) {
		PT p = pts[i];
		while (f < i && sq(p.first - pts[f].first) >= d) {
			st.erase(its[f++]);
		}
		auto u = st.upper_bound(p);
		{
			auto t = u;
			while (true) {
				if (t == begin(st)) break;
				t = prev(t);
				update(*t, p);
				if (sq(p.second - t->second) >= d) break;
			}
		}
		{
			auto t = u;
			while (true) {
				if (t == end(st)) break;
				if (sq(p.second - t->second) >= d) break;
				update(*t, p);
				t = next(t);
			}
		}
		its[i] = st.emplace_hint(u, p);
	}

	return {d, pa, pb};
}

}  // namespace closest_pair_impl