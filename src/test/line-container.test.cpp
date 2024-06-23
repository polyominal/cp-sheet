#include <catch2/catch_test_macros.hpp>

#include "data-structure/line-container.hpp"
#include "util/random.hpp"

TEST_CASE("Line containers: large random", "[line-container]") {
	auto rng = Random(1923);

	for (int Q : {1, 30, 200}) {
		using line_container::LineContainer;
		const i64 MAX = 1e9;
		const i64 INF = 4e18;

		Vec<pair<i64, i64>> lines;
		LineContainer lc_min, lc_max;
		auto add_line = [&]() -> void {
			i64 m = rng.uniform<i64>(-MAX, MAX);
			i64 b = rng.uniform<i64>(-MAX, MAX);
			lines.emplace_back(m, b);
			lc_min.add(-m, -b);
			lc_max.add(m, b);
		};

		const int N = Q + 10;
		for (int i = 0; i < N; i++) {
			add_line();
		}

		for (int q = 0; q < Q; q++) {
			if (rng.uniform_bool()) {
				add_line();
			}

			i64 x = rng.uniform(-MAX, MAX);
			i64 mi = INF, ma = -INF;
			for (auto [m, b] : lines) {
				i64 v = m * x + b;
				mi = min(mi, v);
				ma = max(ma, v);
			}

			REQUIRE(mi == -lc_min.query(x));
			REQUIRE(ma == lc_max.query(x));
		}
	}
}