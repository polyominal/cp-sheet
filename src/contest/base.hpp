#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <string>

using std::abs, std::sin, std::cos, std::tan, std::asin, std::acos, std::atan2;
using std::min, std::max, std::swap;
using std::pair, std::tuple;
using std::set, std::map, std::multiset;
using std::tie;
using std::vector, std::array, std::string;

template <class T> using Vec = vector<T>;
template <class T> using Opt = std::optional<T>;

using i8 = int8_t;
using u8 = uint8_t;
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

inline std::mt19937_64 mt(
	std::chrono::steady_clock::now().time_since_epoch().count());

template <class T> T rand_int(T l, T r) {
	return std::uniform_int_distribution<T>(l, r)(mt);
}