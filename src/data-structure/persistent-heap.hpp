#pragma once

#include "contest/base.hpp"

// Smaller elements are prioritized
template <class T>
struct HeapManager {
    using Heap = int;
    static constexpr Heap null = -42;

    Heap make_empty() { return null; }
    Heap make_copy(Heap h) {
        int i = int(size(nodes));
        nodes.push_back(nodes[h]);
        return i;
    }
    Heap make_single(const T& val) {
        int i = int(size(nodes));
        nodes.push_back(Node{null, null, val});
        return i;
    }

    Heap meld(Heap a, Heap b) {
        if (a == null) {
            return b;
        }
        if (b == null) {
            return a;
        }
        if (nodes[a].v > nodes[b].v) {
            swap(a, b);
        }
        a = make_copy(a);
        nodes[a].ri = meld(nodes[a].ri, b);
        swap(nodes[a].li, nodes[a].ri);
        return a;
    }
    Heap push(Heap h, const T& x) { return meld(h, make_single(x)); }
    // Undefined if h is null
    Heap pop(Heap h) { return meld(nodes[h].li, nodes[h].ri); }

    Opt<T> top(Heap h) {
        if (h != null) {
            return nodes[h].v;
        } else {
            return std::nullopt;
        }
    }

    struct Node {
        Heap li, ri;
        T v;
    };
    Vec<Node> nodes;
};