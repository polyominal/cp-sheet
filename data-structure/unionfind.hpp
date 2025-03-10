#pragma once

#include "contest/base.hpp"

struct UnionFind {
    Vec<int> d;
    UnionFind(int n) { d.assign(n, -1); }
    int get(int a) { return d[a] < 0 ? a : (d[a] = get(d[a])); }
    bool same(int a, int b) { return get(a) == get(b); }
    Opt<pair<int, int>> unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) {
            return std::nullopt;
        }
        if (-d[a] < -d[b]) {
            swap(a, b);
        }
        d[a] += d[b];
        d[b] = a;
        return pair<int, int>{a, b};
    }
};