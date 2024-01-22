/**
 * Author: Hanfei Chen
 * Date: 2024-01-13
 * Description: Given $a \in S$ and $b \ge 0$ where $S$
 * is a monoid, computes $a^b$
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