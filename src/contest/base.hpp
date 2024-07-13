/**
 * Description: Somehow type this up before you do anything
 */

#pragma once

#include <bits/stdc++.h>

using std::vector, std::array, std::string;
using std::set, std::map, std::multiset;
using std::min, std::max, std::swap;
using std::pair, std::tuple;
using std::tie;
using std::abs, std::sin, std::cos, std::tan, std::asin, std::acos, std::atan2;

template <class T> using Vec = vector<T>;
template <class T> using Opt = std::optional<T>;

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

template <class F> struct yc_result { /// start-hash
	F f;
	template <class T> explicit yc_result(T&& f_) : f(std::forward<T>(f_)) {}
	template <class... A> decltype(auto) operator()(A&&... as) {
		return f(std::ref(*this), std::forward<A>(as)...);
	}
};
template <class F> decltype(auto) yc(F&& f) {
	return yc_result<std::decay_t<F>>(std::forward<F>(f));
} /// end-hash

inline std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());