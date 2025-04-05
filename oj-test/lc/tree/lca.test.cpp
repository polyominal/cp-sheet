// verification-helper: PROBLEM https://judge.yosupo.jp/problem/lca

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "tree/hld.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    auto sc = fast_input::Scanner(stdin);

    int N, Q;
    sc >> N >> Q;

    auto hld = HLD(N);
    for (int i = 1; i < N; i++) {
        int p;
        sc >> p;
        hld.add_edge(p, i);
    }
    hld.build();

    for (int q = 0; q < Q; q++) {
        int a, b;
        sc >> a >> b;

        std::cout << hld.lca(a, b) << '\n';
    }

    return 0;
}