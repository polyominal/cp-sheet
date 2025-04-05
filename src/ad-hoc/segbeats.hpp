#pragma once

#include "contest/base.hpp"

template <class Node>
struct Segbeats {
    int sz, h;
    Vec<Node> d;
    template <class A>
    Segbeats(int n, A a) {
        sz = std::bit_ceil<u32>(n);
        h = std::countr_zero<u32>(sz);
        d.resize(2 * sz);
        for (int i = 0; i < n; ++i) {
            d[sz + i] = Node(a(i));
        }
        for (int i = sz - 1; i; --i) {
            update(i);
        }
    }

    void push(int i) { d[i].push(d[2 * i + 0], d[2 * i + 1]); }
    void update(int i) { d[i].update(d[2 * i + 0], d[2 * i + 1]); }

    template <class T>
    void apply(int l, int r, T x) {
        if (l == r) {
            return;
        }
        l += sz, r += sz;
        for (int i = h; i >= 1; i--) {
            if (((l >> i) << i) != l) {
                push(l >> i);
            }
            if (((r >> i) << i) != r) {
                push((r - 1) >> i);
            }
        }
        for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
            if (a & 1) {
                d[a++].apply(x);
            }
            if (b & 1) {
                d[--b].apply(x);
            }
        }
        for (int i = 1; i <= h; i++) {
            if (((l >> i) << i) != l) {
                update(l >> i);
            }
            if (((r >> i) << i) != r) {
                update((r - 1) >> i);
            }
        }
    }

    template <class F>
    void query(int l, int r, F f) {
        if (l == r) {
            return;
        }
        l += sz, r += sz;
        for (int i = h; i >= 1; i--) {
            if (((l >> i) << i) != l) {
                push(l >> i);
            }
            if (((r >> i) << i) != r) {
                push((r - 1) >> i);
            }
        }
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                f(d[l++]);
            }
            if (r & 1) {
                f(d[--r]);
            }
        }
    }

    template <class T>
    void apply(int i, T x) {
        bool res = d[i].apply(x);
        if (i < sz && !res) {
            push(i);
            apply(2 * i, x);
            apply(2 * i + 1, x);
            update(i);
        }
    }
};