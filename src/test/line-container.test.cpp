#include <catch2/catch_test_macros.hpp>

#include "data-structure/line-container.hpp"
#include "util/random.hpp"

TEST_CASE("Line containers: large random", "[line-container]") {
	auto rng = Random(1923);

	for (int Q : {1, 30, 200}) {
		using line_container::LineContainer;
		const ll MAX = 1e9;
		const ll INF = 4e18;

		V<pair<ll, ll>> lines;
		LineContainer lc_min, lc_max;
		auto add_line = [&]() -> void {
			ll m = rng.uniform<ll>(-MAX, MAX);
			ll b = rng.uniform<ll>(-MAX, MAX);
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

			ll x = rng.uniform(-MAX, MAX);
			ll mi = INF, ma = -INF;
			for (auto [m, b] : lines) {
				ll v = m * x + b;
				mi = min(mi, v);
				ma = max(ma, v);
			}

			REQUIRE(mi == -lc_min.query(x));
			REQUIRE(ma == lc_max.query(x));
		}
	}
}