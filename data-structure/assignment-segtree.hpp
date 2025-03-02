#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2024-01-30
 * Description: Range assignment and range composition
 * on a sequence of monoid
 * Source: https://maspypy.com/library-checker-range-set-range-composite
 * Status: Tested with https://judge.yosupo.jp/problem/range_set_range_composite
 */

#include "contest/base.hpp"
#include "data-structure/fast-set.hpp"
#include "data-structure/segtree.hpp"

template <typename T>
    requires Monoid<T>
struct AssignmentSegtree {
    int n;
    Segtree<T> st;
    FastSet cut;
    Vec<T> dat;

    AssignmentSegtree() : n(0), st() {}
    template <class A>
    AssignmentSegtree(int n_, A a) : n(n_), st() {
        build(n_, a);
    }
    template <class A>
    void build(int n_, A a) {
        n = n_;
        st.build(n, a);
        init();
    }
    void init() {
        cut = FastSet(n);
        for (int p = 0; p < n; p++) {
            cut.set(p);
        }
        dat = st.to_array();
    }

    T pow(T s, int b) {
        T r = T::e();
        while (b) {
            if (b & 1) {
                r = r.merge(s);
            }
            s = s.merge(s);
            b >>= 1;
        }
        return r;
    }

    T prod(int l, int r) {
        if (l == r) {
            return T::e();
        }
        int a = cut.prev(l);
        int b = cut.next(l);
        int c = cut.prev(r);
        if (a == c) {
            return pow(dat[a], r - l);
        }
        T u = pow(dat[a], b - l);
        T v = st.prod(b, c);
        T w = pow(dat[c], r - c);
        return u.merge(v).merge(w);
    }

    void assign(int l, int r, const T& s) {
        if (l == r) {
            return;
        }
        int a = cut.prev(l);
        int b = cut.next(r);
        if (a < l) {
            st.set(a, pow(dat[a], l - a));
        }
        if (r < b) {
            T t = dat[cut.prev(r)];
            dat[r] = t;
            cut.set(r);
            st.set(r, pow(t, b - r));
        }
        cut.enumerate(l + 1, r, [&](int i) -> void {
            st.set(i, T::e());
            cut.reset(i);
        });
        dat[l] = s;
        cut.set(l);
        st.set(l, pow(s, r - l));
    }
};
