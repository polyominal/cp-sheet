/**
 * Description: Somehow type this up before you do anything
 */

#pragma once

#include <bits/stdc++.h>
using namespace std;

template <class T> using Vec = vector<T>;

using i64 = int64_t;

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

static mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());