// verification-helper: PROBLEM https://judge.yosupo.jp/problem/closest_pair

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "geometry/closest-pair.hpp"

using P = pair<i64, i64>;

pair<int, int> solve(const Vec<P>& pts) {
	auto best = closest_pair_impl::closest_pair(pts);
	const auto p0 = get<1>(best);
	const auto p1 = get<2>(best);
	if (p0 != p1) {
		auto get_idx = [&](const P& p) -> int {
			return int(std::find(begin(pts), end(pts), p) - begin(pts));
		};
		return {get_idx(get<1>(best)), get_idx(get<2>(best))};
	} else {
		// must find two different indices
		auto it0 = std::find(begin(pts), end(pts), p0);
		auto it1 = std::find(next(it0), end(pts), p0);
		return {int(it0 - begin(pts)), int(it1 - begin(pts))};
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = fast_input::Scanner(stdin);

	int T;
	sc >> T;
	while (T--) {
		int N;
		sc >> N;
		auto pts = Vec<P>(N);
		for (auto& [x, y] : pts) {
			sc >> x >> y;
		}

		auto res = solve(pts);
		std::cout << res.first << ' ' << res.second << '\n';
	}

	return 0;
}