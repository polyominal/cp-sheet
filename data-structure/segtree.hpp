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

#include "contest/base.hpp"

template <class M>
struct Segtree {
    using S = M::S;
    M m;
    Vec<S> d;
    int n, h, sz;
    Segtree(M m_) : m(m_), n(0), h(0), sz(0) {}
    template <class A>
    Segtree(int n_, A a, M m_) : m(m_) {
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
            d[sz + i] = m.e();
        }
        for (int i = sz - 1; i >= 1; i--) {
            update(i);
        }
    }  /// end-hash

    void update(int i) {  /// start-hash
        d[i] = m.op(d[2 * i], d[2 * i + 1]);
    }  /// end-hash

    S prod(int l, int r) {  /// start-hash
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return m.e();
        }
        l += sz, r += sz;
        S sl = m.e(), sr = m.e();
        for (int a = l, b = r; a < b; a /= 2, b /= 2) {
            if (a & 1) {
                sl = m.op(sl, d[a++]);
            }
            if (b & 1) {
                sr = m.op(d[--b], sr);
            }
        }
        return m.op(sl, sr);
    }  /// end-hash

    const S& all_prod() const { return d[1]; }

    Vec<S> to_array() const {
        return Vec<S>(d.begin() + sz, d.begin() + sz + n);
    }

    void set(int p, S s) {  /// start-hash
        assert(0 <= p && p < n);
        p += sz;
        d[p] = s;
        for (int i = 1; i <= h; i++) {
            update(p >> i);
        }
    }  /// end-hash
};