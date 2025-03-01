#pragma once

#include "contest/base.hpp"

template <class C, class D, class E>
struct MinCostFlow {
    static constexpr D INF = std::numeric_limits<D>::max();
    int n;
    Vec<Vec<E>> g;
    int s, t;
    C nc, tot_flow = 0;
    D nd, tot_cost = 0;
    Vec<D> dual;
    Vec<int> pv, pe;
    MinCostFlow(Vec<Vec<E>> g_, int s_, int t_, bool neg)
        : n(int(g_.size())), g(g_), s(s_), t(t_) {
        assert(s != t);
        dual = Vec<D>(n);
        pv = pe = Vec<int>(n);
        // There might be less costly ways to do this
        if (neg) {
            auto dist = Vec<D>(n, INF);
            dist[s] = 0;
            for (int ph = 0; ph < n; ph++) {
                for (int i = 0; i < n; i++) {
                    for (auto e : g[i]) {
                        if (!e.cap || dist[i] == INF) {
                            continue;
                        }
                        dist[e.to] = min(dist[e.to], dist[i] + e.dist);
                    }
                }
            }
            for (int v = 0; v < n; v++) {
                dual[v] += dist[v];
            }
        }
        dual_ref();
    }

    C single_flow(C c) {  /// start-hash
        if (nd == INF) {
            return nc;
        }
        c = min(c, nc);
        for (int v = t; v != s; v = pv[v]) {
            E& e = g[pv[v]][pe[v]];
            e.cap -= c;
            g[v][e.rev].cap += c;
        }
        tot_flow += c;
        tot_cost += nd * c;
        nc -= c;
        if (!nc) {
            dual_ref();
        }
        return c;
    }  /// end-hash

    void max_flow(C c) {  /// start-hash
        while (c) {
            C f = single_flow(c);
            if (!f) {
                break;
            }
            c -= f;
        }
    }  /// end-hash

    void dual_ref() {
        auto dist = Vec<D>(n, INF);  /// start-hash
        pv.assign(n, -1);
        pe.assign(n, -1);
        struct Q {
            D key;
            int to;
            bool operator<(Q r) const { return key > r.key; }
        };
        auto que = std::priority_queue<Q>();
        dist[s] = 0;
        que.push(Q{D(0), s});
        auto vis = Vec<u8>(n);  /// end-hash
        while (!que.empty()) {  /// start-hash
            int v = que.top().to;
            que.pop();
            if (v == t) {
                break;
            }
            if (vis[v]) {
                continue;
            }
            vis[v] = 1;
            for (int i = 0; i < int(g[v].size()); i++) {
                E e = g[v][i];
                if (vis[e.to] || !e.cap) {
                    continue;
                }
                D cost = dist[v] + e.dist + dual[v] - dual[e.to];
                if (dist[e.to] > cost) {
                    dist[e.to] = cost;
                    pv[e.to] = v;
                    pe[e.to] = i;
                    que.push(Q{dist[e.to], e.to});
                }
            }
        }  /// end-hash
        if (dist[t] == INF) {  /// start-hash
            nd = INF;
            nc = 0;
            return;
        }
        for (int v = 0; v < n; v++) {
            if (!vis[v]) {
                continue;
            }
            dual[v] += dist[v] - dist[t];
        }
        nd = dual[t] - dual[s];
        assert(0 <= nd);
        nc = std::numeric_limits<C>::max();
        for (int v = t; v != s; v = pv[v]) {
            nc = min(nc, g[pv[v]][pe[v]].cap);
        }  /// end-hash
    }
};

template <class C, class D, class E>
MinCostFlow<C, D, E> get_mcf(const Vec<Vec<E>>& g,
                             int s,
                             int t,
                             bool neg = false) {
    return MinCostFlow<C, D, E>(g, s, t, neg);
}

// struct E {
// 	int to, rev;
// 	i64 cap, dist;
// };
// auto add_edge = [&](int from, int to, i64 cap, i64 dist) {
// 	g[from].push_back(E{to, int(g[to].size()), cap, dist});
// 	g[to].push_back(E{from, int(g[from].size()) - 1, 0, -dist});
// };