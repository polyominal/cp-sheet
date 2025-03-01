#pragma once

/**
 * Date: 2024-09-14
 * Source: Gifted infants library
 */

#include "contest/base.hpp"

template <class C>
struct MaxFlow {
    C flow;
    Vec<char> dual;  // false: S-side true: T-side
};

template <class C, class E>
MaxFlow<C> get_mf(Vec<Vec<E>>& g, int s, int t, C eps) {
    static constexpr C INF = std::numeric_limits<C>::max();
    MaxFlow<C> info;
    C& flow = (info.flow = 0);
    int n = int(g.size());
    auto level = Vec<int>(n);
    auto iter = Vec<size_t>(n);
    while (true) {
        auto que = Vec<int>{s};  /// start-hash
        level.assign(n, -1);
        level[s] = 0;
        for (size_t z = 0; z < que.size(); z++) {
            int v = que[z];
            for (E e : g[v]) {
                if (e.cap <= eps || level[e.to] >= 0) {
                    continue;
                }
                level[e.to] = level[v] + 1;
                que.push_back(e.to);
            }
        }
        if (level[t] == -1) {
            break;  /// end-hash
        }
        iter.assign(n, 0);
        while (true) {  /// start-hash
            auto dfs = [&](auto self, int v, C f) -> C {
                if (v == t) {
                    return f;
                }
                C res = 0;
                for (auto& i = iter[v]; i < g[v].size(); i++) {
                    E& e = g[v][i];
                    if (e.cap <= eps || level[v] >= level[e.to]) {
                        continue;
                    }
                    C d = self(self, e.to, min(f, e.cap));
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    res += d;
                    f -= d;
                    if (f == 0) {
                        break;
                    }
                }
                return res;
            };
            C f = dfs(dfs, s, INF);
            if (!f) {
                break;
            }
            flow += f;
        }  /// end-hash
    }
    for (int i = 0; i < n; i++) {
        info.dual.push_back(level[i] == -1);
    }
    return info;
}

// struct E {
// 	int to, rev;
// 	i64 cap;
// };
// auto add_edge = [&](int from, int to, i64 cap) {
// 	int i = int(g[from].size()), j = int(g[to].size());
// 	g[from].push_back({to, j, cap});
// 	g[to].push_back({from, i, 0});
// };