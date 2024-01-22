#include <catch2/catch_test_macros.hpp>

#include "ad-hoc/floor-ceil-range.hpp"

TEST_CASE("Floor ranges", "[floor-ceil-range]") {
	using T = tuple<ll, ll, ll>;
	auto get_ranges = [&](ll N) -> V<T> {
		V<T> res;
		auto f = [&](ll q, ll l, ll r) -> void {
			res.emplace_back(q, l, r);
		};
		floor_range(N, f);
		return res;
	};
	auto get_ranges_slow = [&](ll N) -> V<T> {
		VV<ll> buf(N + 1);
		for (ll x = 1; x <= N; x++) {
			buf[N / x].push_back(x);
		}
		V<T> res;
		for (ll x = 1; x <= N; x++) {
			if (!buf[x].empty()) {
				ll lo = buf[x][0];
				ll hi = buf[x].back();
				res.emplace_back(x, lo, hi + 1);
			}
		}
		return res;
	};
	for (ll N = 1; N <= 200; N++) {
		REQUIRE(get_ranges(N) == get_ranges_slow(N));
	}
}

TEST_CASE("Ceil ranges", "[floor-ceil-range]") {
	using T = tuple<ll, ll, ll>;
	auto get_ranges = [&](ll N) -> V<T> {
		V<T> res;
		auto f = [&](ll q, ll l, ll r) -> void {
			res.emplace_back(q, l, r);
		};
		ceil_range(N, f);
		return res;
	};
	auto get_ranges_slow = [&](ll N) -> V<T> {
		VV<ll> buf(N + 1);
		for (ll x = 1; x <= N; x++) {
			buf[(N-1) / x + 1].push_back(x);
		}
		V<T> res;
		for (ll x = 1; x <= N; x++) {
			if (x == 1) {
				res.emplace_back(x, N, numeric_limits<ll>::max());
				continue;
			}
			if (!buf[x].empty()) {
				ll lo = buf[x][0];
				ll hi = buf[x].back();
				res.emplace_back(x, lo, hi + 1);
			}
		}
		return res;
	};
	for (ll N = 1; N <= 200; N++) {
		REQUIRE(get_ranges(N) == get_ranges_slow(N));
	}
}