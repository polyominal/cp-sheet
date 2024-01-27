/**
 * Author: Hanfei Chen
 * Date: 2023-09-15
 * Description: Frees you from writing $\%\, \text{mod}$ stuff.
 * This only works with prime modulo numbers that are
 * determined during compile-time
 * Status: Tested with many
 */

#pragma once

#include "contest/base.hpp"

template <class T> T pow(T a, ll b) {
	assert(b >= 0);
	T r = 1;
	while (b) {
		if (b & 1) r *= a;
		a *= a;
		b >>= 1;
	}
	return r;
}

template <uint32_t mod> struct mint {
	using U = uint32_t;

	static constexpr U m = mod; /// start-hash
	U v;
	constexpr mint() : v(0) {}
	constexpr mint(ll a) { s(U(a % m + m)); }
	constexpr mint& s(U a) { v = a < m ? a : a-m; return *this; }
	friend mint inv(const mint& n) { return pow(n, m-2); } /// end-hash

	mint operator- () const { /// start-hash
		mint res;
		res.v = v ? m-v : 0;
		return res;
	} /// end-hash

	friend bool operator == (const mint& a, const mint& b) { return a.v == b.v; } /// start-hash
	friend bool operator != (const mint& a, const mint& b) { return !(a == b); } /// end-hash

	mint& operator += (const mint& o) { return s(v + o.v); } /// start-hash
	mint& operator -= (const mint& o) { return s(v + m - o.v); }
	mint& operator *= (const mint& o) { v = U(uint64_t(v) * o.v % m); return *this; }
	mint& operator /= (const mint& o) { return *this *= inv(o); } /// end-hash

	friend mint operator + (const mint& a, const mint& b) { return mint(a) += b; } /// start-hash
	friend mint operator - (const mint& a, const mint& b) { return mint(a) -= b; }
	friend mint operator * (const mint& a, const mint& b) { return mint(a) *= b; }
	friend mint operator / (const mint& a, const mint& b) { return mint(a) /= b; } /// end-hash

	static constexpr U get_mod() { return m; }
	static constexpr mint get_root() {
		if (m == 998244353) return 3;
		if (m == 1053818881) return 2789;
		assert(false);
	}
};