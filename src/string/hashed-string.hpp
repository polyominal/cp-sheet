#pragma once

#include "contest/base.hpp"

template <class H> struct HashedManager {
	const H base;
	Vec<H> pows;
	HashedManager(const H& base_) : base(base_), pows({H(1)}) {}

	using Hashed = Vec<H>;
	template <class S> Hashed make(const S& s) {
		size_t n = size(s);
		while (size(pows) <= n) {
			pows.push_back(pows.back() * base);
		}
		auto hs = Hashed(n + 1);
		hs[0] = H(0);
		for (size_t i = 0; i < n; i++) {
			hs[i + 1] = hs[i] * base + H(s[i]);
		}
		return hs;
	}
	H get(const Hashed& hs, int l, int r) const {
		return hs[r] - hs[l] * pows[r - l];
	}
};