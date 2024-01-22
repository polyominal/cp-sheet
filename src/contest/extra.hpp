#pragma once

#include "contest/base.hpp"

using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

namespace internal {

inline int next_pow2(int n) {
	int k = 0;
	while ((uint32_t(1) << k) < uint32_t(n)) k++;
	return k;
}

} // namespace internal