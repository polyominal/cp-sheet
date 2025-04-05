#pragma once

#include "contest/base.hpp"
#include "data-structure/flatten-vector.hpp"

struct HLD {
    int n;
    Vec<int> ord, iord, sz;
    Vec<int> depth;
    Vec<pair<int, int>> path;
    Vec<pair<int, int>> edges;
    HLD(int n_) : n(n_), iord(n), sz(n, 1), depth(n), path(n) {}

    void add_edge(int a, int b) {
        edges.emplace_back(a, b);
        edges.emplace_back(b, a);
    }

    void build(int r = 0) {
        auto tr = FlattenVector<int>(n, edges);

        auto par = Vec<int>(n, -1);  /// start-hash
        auto topo = Vec<int>{r};
        topo.reserve(n);
        for (int z = 0; z < n; z++) {
            int v = topo[z];
            for (int w : tr[v]) {
                if (w == par[v]) {
                    continue;
                }
                par[w] = v;
                depth[w] = depth[v] + 1;
                topo.push_back(w);
            }
        }  /// end-hash

        auto max_ch = Vec<int>(n, -1);  /// start-hash
        for (int v : topo | std::views::drop(1) | std::views::reverse) {
            int p = par[v];
            sz[p] += sz[v];
            if (max_ch[p] == -1 || sz[max_ch[p]] < sz[v]) {
                max_ch[p] = v;
            }
        }  /// end-hash

        auto stk = Vec<pair<int, bool>>{{r, true}};  /// start-hash
        stk.reserve(n);
        while (!stk.empty()) {
            auto [v, ir] = stk.back();
            stk.pop_back();
            int i = int(size(ord));
            ord.push_back(v);
            iord[v] = i;
            if (ir) {
                path[i] = {par[v] == -1 ? -1 : iord[par[v]], 1};
            } else {
                path[i] = {path[i - 1].first, path[i - 1].second + 1};
            }
            if (max_ch[v] == -1) {
                continue;
            }
            for (int w : tr[v]) {
                if (w == par[v] || w == max_ch[v]) {
                    continue;
                }
                stk.emplace_back(w, true);
            }
            stk.emplace_back(max_ch[v], false);
        }  /// end-hash
    }

    bool in_subtree(int a, int v) const {
        return iord[a] <= iord[v] && iord[v] < iord[a] + sz[a];
    }

    Opt<int> get_ancestor(int a, int k) const {  /// start-hash
        assert(k >= 0);
        a = iord[a];
        while (a != -1 && k) {
            if (k >= path[a].second) {
                k -= path[a].second;
                a = path[a].first;
            } else {
                a -= k;
                k = 0;
            }
        }
        if (a != -1) {
            return ord[a];
        } else {
            return std::nullopt;
        }
    }  /// end-hash

    int lca(int a, int b) const {  /// start-hash
        a = iord[a], b = iord[b];
        while (true) {
            if (a > b) {
                swap(a, b);
            }
            if (a > b - path[b].second) {
                return ord[a];
            }
            b = path[b].first;
        }
    }  /// end-hash

    Opt<int> jump(int s, int t, int d) const {  /// start-hash
        int w = lca(s, t);
        if (d <= depth[s] - depth[w]) {
            return get_ancestor(s, d);
        } else {
            d = (depth[s] + depth[t] - 2 * depth[w]) - d;
            if (d >= 0) {
                return get_ancestor(t, d);
            } else {
                return std::nullopt;
            }
        }
    }  /// end-hash

    Vec<pair<int, int>> extract(int s, int t) {  /// start-hash
        static Vec<pair<int, int>> res;
        res.clear();
        s = iord[s], t = iord[t];
        while (true) {
            if (t > s - path[s].second) {
                res.emplace_back(s, t + 1);
                break;
            }
            res.emplace_back(s, s - path[s].second + 1);
            s = path[s].first;
        }
        return res;
    }  /// end-hash

    template <bool vertex = true>
    void apply(int s, int t, std::function<void(int, int)> f) {  /// start-hash
        int a = lca(s, t);
        for (auto&& [x, y] : extract(s, a)) {
            f(x + 1, y);
        }
        if constexpr (vertex) {
            f(iord[a], iord[a] + 1);
        }
        auto des = extract(t, a);
        for (auto&& [x, y] : des | std::views::reverse) {
            f(y, x + 1);
        }
    }  /// end-hash

    int get_lowest(int a, std::function<bool(int)> f) const {  /// start-hash
        a = iord[a];
        while (a != -1) {
            int t = a - path[a].second + 1;
            if (!f(ord[t])) {
                a = path[a].first;
                continue;
            }
            int mi = t, ma = a + 1;
            while (ma - mi > 1) {
                int md = (mi + ma) / 2;
                if (f(ord[md])) {
                    mi = md;
                } else {
                    ma = md;
                }
            }
            return ord[mi];
        }
        return -1;
    }  /// end-hash

    Vec<int> inds;
    pair<Vec<int>, Vec<int>> compress(Vec<int> vs) {  /// start-hash
        inds.resize(n, -1);
        auto cmp = [&](int a, int b) { return iord[a] < iord[b]; };
        std::ranges::sort(vs, cmp);
        vs.erase(unique(begin(vs), end(vs)), end(vs));
        int num = int(size(vs));
        assert(num >= 1);
        for (int z = 1; z < num; z++) {
            vs.push_back(lca(vs[z - 1], vs[z]));
        }

        std::ranges::sort(vs, cmp);
        vs.erase(unique(begin(vs), end(vs)), end(vs));
        num = int(size(vs));
        for (int z = 0; z < num; z++) {
            inds[vs[z]] = z;
        }
        Vec<int> par(num, -1);
        for (int z = 1; z < num; z++) {
            par[z] = inds[lca(vs[z - 1], vs[z])];
        }
        return {vs, par};
    }  /// end-hash
};