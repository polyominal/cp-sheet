#pragma once

#include "contest/base.hpp"

struct DFSTree {
    struct Inner {
        Vec<int> ord;
        Vec<int> par;

        template <class G>
        Inner(const G& g) {
            int n = int(g.size());
            ord.reserve(n);
            par = Vec<int>(n, -2);
            auto its = Vec<decltype(g[0].begin())>(n);
            for (int v = 0; v < n; v++) {
                its[v] = g[v].begin();
            }
            for (int r = 0; r < n; r++) {
                if (par[r] != -2) {
                    continue;
                }
                par[r] = -1;
                ord.push_back(r);
                int v = r;
                while (v >= 0) {
                    auto& it = its[v];
                    if (it == g[v].end()) {
                        v = par[v];
                        continue;
                    }
                    if (int w = *it; par[w] == -2) {
                        par[w] = v;
                        v = w;
                        ord.push_back(v);
                    }
                    it = std::next(it);
                }
            }
        }

        Vec<int> get_iord() const {
            int n = int(par.size());
            auto iord = Vec<int>(n);
            for (int i = 0; i < n; i++) {
                iord[ord[i]] = i;
            }
            return iord;
        }
    };

    template <class G>
    static auto make(const G& g) {
        return Inner(g);
    }
};