#pragma once

/**
 * Source: https://nyaannyaan.github.io/library/dp/monge-d-edge-shortest-path.hpp
 * Status: Good luck
 */

#include "ad-hoc/golden-section-search.hpp"
#include "ad-hoc/monge-shortest-path.hpp"

inline i64 monge_fixed_len_shortest_path(
	int N,
	int D,
	i64 upper,
	const std::function<i64(int, int)>& f) {
	using T = i128;
	upper = abs(upper);
	static constexpr T INF = std::numeric_limits<T>::max() / 2;
	auto dp = [&](i64 x) -> T {
		auto g = [&](int from, int to) -> T { return f(from, to) + x; };
		T cost = monge_shortest_path<T>(N, g, INF)[N];
		return cost - T{1} * D * x;
	};
	return i64(golden_section_search<T, false>(dp, -upper, upper).second);
}