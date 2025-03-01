#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2023-11-20
 * Description: Self-explanatory string hashing structure
 * Source: https://yosupo.hatenablog.com/entry/2023/08/06/181942
 * Status: Tested with https://judge.yosupo.jp/problem/suffixarray
 */

#include "contest/base.hpp"

struct HashInt {
    using H = HashInt;  /// start-hash
    using T = unsigned long long;
    using L = u128;
    static constexpr T m = (T(1) << 61) - 1;
    static constexpr T m8 = m * 8;
    T v;
    HashInt() : v(0) {}
    HashInt(T a) : v(a % m * 8) {}
    T get() const { return v == m8 ? 0 : v; }  /// end-hash

    H& operator+=(const H& o) {  /// start-hash
        if (__builtin_uaddll_overflow(v, o.v, &v)) {
            v -= m8;
        }
        return *this;
    }
    H& operator-=(const H& o) {
        if (__builtin_usubll_overflow(v, o.v, &v)) {
            v += m8;
        }
        return *this;
    }  /// end-hash

    H& operator*=(const H& o) {  /// start-hash
        L t = L(v) * o.v;
        T x = T(t >> 67 << 3);
        T y = T(t << 61 >> 64);
        if (__builtin_uaddll_overflow(x, y, &v)) {
            v -= m8;
        }
        return *this;
    }  /// end-hash

    friend H operator+(const H& a, const H& b) {
        return H(a) += b;
    }  /// start-hash
    friend H operator-(const H& a, const H& b) { return H(a) -= b; }
    friend H operator*(const H& a, const H& b) { return H(a) *= b; }
    friend bool operator==(const H& a, const H& b) {
        return a.get() == b.get();
    }  /// end-hash
};
