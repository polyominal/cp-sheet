#pragma once

/**
 * Author: Hanfei Chen
 * Description: Lazy segtree abstraction
 * Source: ac-library and many others
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/range_affine_range_sum (apply, prod)
 * - https://judge.yosupo.jp/problem/range_affine_point_get (point_get)
 * - https://atcoder.jp/contests/practice2/tasks/practice2_j (max_right)
 * - 2023 Nanjing Regionals Problem M (almost everything?)
 * - https://judge.yosupo.jp/problem/vertex_set_path_composite (set; also justified runtime polymorphism!)
 */

#include "algebra/monoidal.hpp"
#include "contest/base.hpp"

template <typename T>
    requires Monoid<T>
struct Segtree {
    Vec<T> d;
    int n, h, sz;
    Segtree() : n(0), h(0), sz(0) {}
    template <class A>
    Segtree(int n_, A a) {
        build(n_, a);
    }

    template <class A>
    void build(int n_, A a) {  /// start-hash
        n = n_;
        sz = std::bit_ceil<uint32_t>(n);
        h = std::countr_zero<uint32_t>(sz);
        d.resize(2 * sz);
        for (int i = 0; i < n; i++) {
            d[sz + i] = a(i);
        }
        for (int i = n; i < sz; i++) {
            d[sz + i] = T::e();
        }
        for (int i = sz - 1; i >= 1; i--) {
            update(i);
        }
    }  /// end-hash

    void update(int i) {  /// start-hash
        d[i] = d[2 * i].merge(d[2 * i + 1]);
    }  /// end-hash

    T prod(int l, int r) const {  /// start-hash
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return T::e();
        }
        l += sz, r += sz;
        T sl = T::e(), sr = T::e();
        for (int a = l, b = r; a < b; a /= 2, b /= 2) {
            if (a & 1) {
                sl = sl.merge(d[a++]);
            }
            if (b & 1) {
                sr = d[--b].merge(sr);
            }
        }
        return sl.merge(sr);
    }  /// end-hash

    const T& all_prod() const { return d[1]; }

    Vec<T> to_array() const {
        return Vec<T>(d.begin() + sz, d.begin() + sz + n);
    }

    void set(int p, const T& s) {  /// start-hash
        assert(0 <= p && p < n);
        p += sz;
        d[p] = s;
        for (int i = 1; i <= h; i++) {
            update(p >> i);
        }
    }  /// end-hash
};