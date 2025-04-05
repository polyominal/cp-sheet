#pragma once

#include "contest/base.hpp"

/**
 * Description: Li-Chao tree for max queries
 */

namespace lichao_impl {

constexpr i64 INF = 2e18;
struct Line {
    i64 k, m;

    i64 at(i64 x) const { return k * x + m; }
    bool over(const Line o, int x) const { return at(x) > o.at(x); }
};
const Line NONE = {0, -INF};
struct Node {
    // static const size_t bs = 450 << 20;
    // static char buf[bs];
    // static size_t i;

    // static void* operator new(size_t s) {
    // 	assert(s < i);
    // 	return &buf[i -= s];
    // }
    // static void reset() { i = bs; }
    array<Node*, 2> c{nullptr, nullptr};
    Line f = NONE;
};
// char Node::buf[Node::bs];
// size_t Node::i = Node::bs;
constexpr int LO = -1.01e9;
constexpr int HI = +1.01e9;

inline Node* insert_inner(Line f, Node* n, int l, int r) {
    if (!n) {
        n = new Node();
    }
    bool l_over = f.over(n->f, l);
    bool r_over = f.over(n->f, r - 1);
    if (l_over == r_over) {
        if (l_over) {
            swap(f, n->f);
        }
    } else {
        int m = (l + r) / 2;
        bool m_over = f.over(n->f, m);
        if (m_over) {
            swap(f, n->f);
        }
        if (l_over != m_over) {
            n->c[0] = insert_inner(f, n->c[0], l, m);
        } else {
            n->c[1] = insert_inner(f, n->c[1], m, r);
        }
    }
    return n;
}

inline Node* insert_outer(const Line& f,
                          Node* n,
                          int l,
                          int r,
                          int ql,
                          int qr) {
    if (qr <= l || r <= ql) {
        // do nothing
    } else {
        if (!n) {
            n = new Node();
        }
        if (ql <= l && r <= qr) {
            insert_inner(f, n, l, r);
        } else {
            int m = (l + r) / 2;
            n->c[0] = insert_outer(f, n->c[0], l, m, ql, qr);
            n->c[1] = insert_outer(f, n->c[1], m, r, ql, qr);
        }
    }
    return n;
}

inline i64 point_query(int x, Node* n, int l, int r) {
    i64 res;
    if (!n) {
        res = -INF;
    } else {
        res = n->f.at(x);
        if (r - l > 1) {
            int m = (l + r) / 2;
            if (x < m) {
                res = max(res, point_query(x, n->c[0], l, m));
            } else {
                res = max(res, point_query(x, n->c[1], m, r));
            }
        }
    }
    return res;
}

}  // namespace lichao_impl