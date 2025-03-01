#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2024-01-12
 * Status:
 * - Unit tested
 * - floor_range tested with https://judge.yosupo.jp/problem/enumerate_quotients
 */

#include "contest/base.hpp"

inline void floor_range(i64 n, auto f) {
    int rt = int(sqrt(double(n)));  /// start-hash
    int num = (i64(rt) * rt + rt <= n ? rt : rt - 1);
    i64 prv = n + 1;
    for (int q = 1; q <= num; q++) {
        i64 x = i64(double(n) / (q + 1)) + 1;
        f(q, x, prv);
        prv = x;
    }
    for (int l = rt; l >= 1; l--) {
        f(i64(double(n) / l), l, l + 1);
    }  /// end-hash
}

inline void ceil_range(i64 n, auto f) {
    int rt = int(sqrt(double(n)));  /// start-hash
    i64 prv = std::numeric_limits<i64>::max();
    for (int q = 1; q <= rt; ++q) {
        i64 x = i64(double(n + q - 1) / q);
        f(q, x, prv);
        prv = x;
    }
    int num = (n <= i64(rt) * rt + rt ? rt : rt + 1);
    if (n == rt * rt) {
        --num;
    }
    for (int l = num; l >= 1; --l) {
        f(i64(double(n + l - 1) / l), l, l + 1);
    }  /// end-hash
}