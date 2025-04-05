#pragma once

/**
 * Author: Hanfei Chen
 * Description: Randomized Treap with split/merge support.
 * \texttt{nodes.size()} < \texttt{nodes.capacity()}
 * must be maintained.
 * One strategy to save space is
 * to refactor everything when the size of \texttt{nodes}
 * is approximating its capacity
 * Source: me
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
 * Time: O(\log N) per operation
 */

#include "algebra/monoidal-sized.hpp"
#include "contest/base.hpp"

template <typename T, typename E, bool persistent = false>
    requires Monoid<T> && EffectWithSize<E, T>
struct TreapManager {
    TreapManager(int alloc = 0) {
        if (alloc > 0) {
            nodes.reserve(alloc);
        } else {
            // make sure to understand what you're doing
            assert(!persistent);
        }

        for (int z = 0; z < 2; z++) {
            states[z] = std::random_device()();
        }
    }

    using Tree = size_t;

    Tree make_empty() { return Tree(null); }

    Tree make_single(const T& s) {  /// start-hash
        nodes.push_back(Node{null, null, 1, false, false, s, s, E::e()});
        return nodes.size() - 1;
    }  /// end-hash

    Tree make_copy(Tree o) { return _make_copy(o); }

    int size(const Tree t) { return _size(t); }
    Tree reverse(Tree t) { return _reverse(t); }
    Tree apply(Tree t, const E& f) { return _apply(t, f); }
    T prod(Tree t) { return _prod(t); }

    Tree split_k(Tree& t, int k) {  /// start-hash
        Tree o;
        tie(t, o) = _split_k(t, k);
        return o;
    }  /// end-hash

    Tree merge(Tree a, Tree b) { return _merge(a, b); }

    Tree build(const Vec<T>& a) {  /// start-hash
        if (a.empty()) {
            return make_empty();
        }
        return _build(a, 0, int(a.size()));
    }  /// end-hash

  private:
    static constexpr Tree null = std::numeric_limits<Tree>::max();

    struct Node {  /// start-hash
        Tree li, ri;
        int sz;
        bool rev, app;
        T a, s;
        E f;
    };
    Vec<Node> nodes;
    Node& node(Tree i) { return nodes[i]; }
    int _size(Tree i) { return i == null ? 0 : node(i).sz; }  /// end-hash

    Tree _make_copy(Tree o) {  /// start-hash
        if constexpr (!persistent) {
            return o;
        }

        if (o == null) {
            return null;
        }
        nodes.push_back(node(o));
        return nodes.size() - 1;
    }  /// end-hash

    Tree _build(const Vec<T>& a, int l, int r) {  /// start-hash
        if (r - l == 1) {
            return make_single(a[l]);
        }
        int md = (l + r) / 2;
        return _merge(_build(a, l, md), _build(a, md, r));
    }  /// end-hash

    void _update(Tree i) {  /// start-hash
        auto& n = node(i);
        n.s = _prod(n.li).merge(n.a.merge(_prod(n.ri)));
        n.sz = size(n.li) + size(n.ri) + 1;
    }  /// end-hash

    Tree _reverse(Tree i) {  /// start-hash
        if (i == null) {
            return i;
        }
        i = _make_copy(i);
        auto& n = node(i);
        n.rev = !n.rev;
        swap(n.li, n.ri);
        return i;
    }  /// end-hash

    T _prod(Tree i) { return i == null ? T::e() : node(i).s; }

    Tree _apply(Tree i, const E& f) {  /// start-hash
        if (i == null) {
            return i;
        }
        i = _make_copy(i);
        auto& n = node(i);
        n.s = f.act(n.s, n.sz);
        n.a = f.act(n.a, 1);
        n.f = f.merge(n.f);
        n.app = true;
        return i;
    }  /// end-hash

    Tree downdate(Tree i) {  /// start-hash
        assert(i != null);
        i = _make_copy(i);
        auto& n = node(i);
        if (n.rev) {
            n.li = _reverse(n.li);
            n.ri = _reverse(n.ri);
            n.rev = false;
        }
        if (n.app) {
            n.li = _apply(n.li, n.f);
            n.ri = _apply(n.ri, n.f);
            n.f = E::e();
            n.app = false;
        }
        return i;
    }  /// end-hash

    template <class F>
    pair<Tree, Tree> _split(Tree i, F go_left) {  /// start-hash
        if (i == null) {
            return {null, null};
        }
        i = downdate(i);
        auto& n = node(i);
        Tree li = n.li, ri = n.ri;
        Tree x, y;
        if (go_left(li, ri)) {
            y = i;
            tie(x, n.li) = _split(n.li, go_left);
        } else {
            x = i;
            tie(n.ri, y) = _split(n.ri, go_left);
        }
        _update(i);
        return {x, y};
    }  /// end-hash

    pair<Tree, Tree> _split_k(Tree i, int k) {  /// start-hash
        return _split(i, [&](Tree li, Tree) -> bool {
            int lsz = size(li);
            if (k <= lsz) {
                return true;
            } else {
                k -= lsz + 1;
                return false;
            }
        });
    }  /// end-hash

    // Use std::mt19937_64 if performance is not an issue
    // https://prng.di.unimi.it/xoroshiro64star.c
    inline u32 rotl(const u32 x, int k) {  /// start-hash
        return (x << k) | (x >> (32 - k));
    }
    u32 states[2];
    u32 rng() {
        const u32 s0 = states[0];
        u32 s1 = states[1];
        const u32 res = s0 * 0x9E3779BB;
        s1 ^= s0;
        states[0] = rotl(s0, 26) ^ s1 ^ (s1 << 9);
        states[1] = rotl(s1, 13);
        return res;
    }  /// end-hash

    Tree _merge(Tree a, Tree b) {  /// start-hash
        if (a == null) {
            return b;
        }
        if (b == null) {
            return a;
        }
        Tree r;
        u32 sa = size(a), sb = size(b);
        if (rng() % (sa + sb) < sa) {
            r = downdate(a);
            node(r).ri = _merge(node(r).ri, b);
        } else {
            r = downdate(b);
            node(r).li = _merge(a, node(r).li);
        }
        _update(r);
        return r;
    }  /// end-hash
};
