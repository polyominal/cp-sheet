// verification-helper: PROBLEM https://judge.yosupo.jp/problem/jump_on_tree

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "graph/hld.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    auto sc = fast_input::Scanner(stdin);

    int N, Q;
    sc.read(N, Q);

    auto adj = Vec<Vec<int>>(N);
    for (int e = 0; e < N-1; e++) {
        int a, b;
        sc.read(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto par = Vec<int>(N);
    auto dfs = [&](auto self, int v, int p) -> void {
        par[v] = p;
        for (int w : adj[v]) {
            if (w != p) {
                self(self, w, v);
            }
        }
    };
    dfs(dfs, 0, -1);

    auto hld = HLD(par);

    for (int q = 0; q < Q; q++) {
        int s, t, i;
        sc.read(s, t, i);

        if (auto v = hld.jump(s, t, i); v.has_value()) {
            std::cout << v.value() << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}