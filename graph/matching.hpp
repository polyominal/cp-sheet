#pragma once

/**
 * Date: 2024-09-13
 * Source: https://github.com/yosupo06/yosupo-library/blob/15046ee7dafa1ba60174fd37b5c03ee9cbe444bf/src/yosupo/matching.hpp
 */

#include "contest/base.hpp"

struct MaxMatching {
    int n;
    Vec<Vec<int>> g;
    Vec<int> mate;
    MaxMatching(int n_) : n(n_), g(n_), mate(n, -1) {}
    void add_edge(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    Vec<pair<int, int>> max_matching() {  /// start-hash
        greedy();
        blossom();
        auto res = Vec<pair<int, int>>();
        for (int i = 0; i < n; i++) {
            if (i < mate[i]) {
                res.emplace_back(i, mate[i]);
            }
        }
        return res;
    }  /// end-hash

    void greedy() {  /// start-hash
        for (int i = 0; i < n; i++) {
            for (int j : g[i]) {
                if (mate[i] == -1 && mate[j] == -1) {
                    mate[i] = mate[j];
                    mate[j] = mate[i];
                }
            }
        }
    }  /// end-hash

    void blossom() {
        auto is_even = Vec<int>(n, -1);
        auto first_ = Vec<int>(n);
        auto nx = Vec<pair<int, int>>(n);

        auto match = [&](auto self, int p, int b) {  /// start-hash
            int d = mate[p];
            mate[p] = b;
            if (d == -1 || mate[d] != p) {
                return;
            }
            if (nx[p].second == -1) {
                mate[d] = nx[p].first;
                self(self, nx[p].first, d);
            } else {
                self(self, nx[p].first, nx[p].second);
                self(self, nx[p].second, nx[p].first);
            }
        };  /// end-hash

        auto augment = [&](int st) {  /// start-hash
            auto first_rec = [&](auto self, int x) {
                if (first_[x] == -1 || is_even[first_[x]] != st) {
                    return first_[x];
                }
                return first_[x] = self(self, first_[x]);
            };
            auto first = [&](int x) { return first_rec(first_rec, x); };

            is_even[st] = st;
            first_[st] = -1;
            nx[st] = {-1, -1};
            auto q = Vec<int>{st};
            for (size_t i = 0; i < q.size(); i++) {
                int a = q[i];
                for (int b : g[a]) {
                    if (b == st) {
                        continue;
                    }
                    if (mate[b] == -1) {
                        mate[b] = a;
                        match(match, a, b);
                        return true;
                    }
                    if (is_even[b] == st) {
                        int x = first(a), y = first(b);
                        if (x == y) {
                            continue;
                        }
                        int z = -1;
                        while (x != -1 || y != -1) {
                            if (y != -1) {
                                swap(x, y);
                            }
                            if (nx[x] == pair<int, int>(a, b)) {
                                z = x;
                                break;
                            }
                            nx[x] = {a, b};
                            x = first(nx[mate[x]].first);
                        }
                        for (int v : {first(a), first(b)}) {
                            while (v != z) {
                                q.push_back(v);
                                is_even[v] = st;
                                first_[v] = z;
                                v = first(nx[mate[v]].first);
                            }
                        }
                    } else if (is_even[mate[b]] != st) {
                        is_even[mate[b]] = st;
                        nx[b] = {-1, -1};
                        nx[mate[b]] = {a, -1};
                        first_[mate[b]] = b;
                        q.push_back(mate[b]);
                    }
                }
            }
            return false;
        };  /// end-hash

        for (int st = 0; st < n; st++) {
            if (mate[st] == -1) {
                augment(st);
            }
        }
    }
};