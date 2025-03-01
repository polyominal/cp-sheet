#pragma once

#include "contest/base.hpp"

template <class T> struct FlattenVector {
	Vec<T> v;
	Vec<int> off;
	template <class U> FlattenVector(int n, U&& a) : off(n + 1) {
		for (const auto& [i, _] : a) {
			off[i + 1]++;
		}
		std::partial_sum(begin(off), end(off), begin(off));

		v = std::vector<T>(off[n]);
		auto pt = off;
		for (auto&& [i, x] : std::forward<U>(a)) {
			v[pt[i]++] = std::move(x);
		}
	}

	auto at(int i) const {
		return v | std::views::take(off[i + 1]) | std::views::drop(off[i]);
	}
	auto operator[](int i) const { return at(i); }

	int size() const { return int(off.size()) - 1; }
};