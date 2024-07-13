#pragma once

#include "data-structure/unionfind.hpp"

template <class F> struct RangeParallelUnionFind {
	Vec<UnionFind> uf;
	const F f;
	RangeParallelUnionFind(int n, F f_) : uf(std::bit_width<u32>(n), n), f(f_) {}
	void inner(int a, int b, int k) {
		if (auto result = uf[k].unite(a, b); result.has_value()) {
			auto [p, v] = result.value();
			if (k == 0) {
				f(p, v);
			} else {
				k--;
				inner(a, b, k);
				inner(a + (1 << k), b + (1 << k), k);
			}
		}
	}
	void unite(int a, int b, int d) {
		if (d == 0) return;
		int k = std::bit_width<u32>(d) - 1;
		inner(a, b, k);
		inner(a + d - (1 << k), b + d - (1 << k), k);
	}
};