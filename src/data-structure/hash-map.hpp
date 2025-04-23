#pragma once

/**
 * Author: Hanfei Chen
 * Description: Faster and safer hash map.
 * For some key type $K$ other than \texttt{uint64\_t},
 * define a custom hash function that maps $K$ to \texttt{uint64\_t}
 * Source:
 * - https://codeforces.com/blog/entry/62393;
 * - https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/data-structures/STL%20(5)/HashMap.h
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/associative_array (int64_t, uint64_t)
 */

#include <ext/pb_ds/assoc_container.hpp>
#include "contest/base.hpp"

struct CustomHash {  /// start-hash
    u64 operator()(u64 x) const {
        static const u64
            z = std::chrono::steady_clock::now().time_since_epoch().count(),
            c = u64(4e18 * acos(0)) + 71;
        return u64(__builtin_bswap64((x ^ z) * c));
    }
};  /// end-hash

template <class K, class V, class Hash = CustomHash>
using HashMap = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <class K, class Hash = CustomHash>
using HashSet = HashMap<K, __gnu_pbds::null_type, Hash>;