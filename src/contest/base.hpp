/**
 * Description: Somehow type this up before you do anything
 */

#pragma once

#include <bits/stdc++.h>
using namespace std;

template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

using ll = int64_t;

template <class F> struct ycr { /// start-hash
	F f;
	template <class T> explicit ycr(T&& f_) : f(forward<T>(f_)) {}

	template <class... A> decltype(auto) operator()(A&&... as) {
		return f(ref(*this), forward<A>(as)...);
	}
};
template <class F> decltype(auto) yc(F&& f) {
	return ycr<decay_t<F>>(forward<F>(f));
} /// end-hash

static mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());