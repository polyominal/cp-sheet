/**
 * Author: Hanfei Chen
 * Description: Faster and safer hash map.
 * Source:
 * - https://codeforces.com/blog/entry/62393;
 * - https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/data-structures/STL%20(5)/HashMap.h
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/associative_array (int64_t, uint64_t)
 */

#pragma once

#include "contest/base.hpp"
#include <ext/pb_ds/assoc_container.hpp>

struct CustomHash { /// start-hash
	size_t operator ()(uint64_t x) const {
		static const uint64_t z = chrono::steady_clock::now().time_since_epoch().count(),
							  c = uint64_t(4e18*acos(0))+71;
		return __builtin_bswap64((x^z)*c);
	}
}; /// end-hash

template <class K, class V, class Hash = CustomHash> /// start-hash
using HashMap = __gnu_pbds::gp_hash_table<K, V, Hash>; /// end-hash

template <class K, class Hash = CustomHash> /// start-hash
using HashSet = HashMap<K, __gnu_pbds::null_type, Hash>; /// end-hash