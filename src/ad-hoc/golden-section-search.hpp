#pragma once

#include "contest/base.hpp"

namespace golden_section_search_impl {

// [min, max]
template <class T, bool get_min = true>
pair<i64, T> golden_section_search(const std::function<T(i64)>& f,
								   i64 min,
								   i64 max) {
	assert(min <= max);
	i64 a = min - 1, x, b;
	{
		i64 s = 1, t = 2;
		while (t < max - min + 2) swap(s += t, t);
		x = a + t - s, b = a + t;
	}
	T fx = f(x), fy;
	while (a + b != 2 * x) {
		i64 y = a + b - x;
		if (max < y || (fy = f(y), get_min ? fx < fy : fx > fy)) {
			b = a;
			a = y;
		} else {
			a = x;
			x = y;
			fx = fy;
		}
	}
	return {x, fx};
}

}  // namespace golden_section_search_impl

using golden_section_search_impl::golden_section_search;