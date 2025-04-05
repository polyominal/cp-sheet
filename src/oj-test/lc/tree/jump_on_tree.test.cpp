// verification-helper: PROBLEM https://judge.yosupo.jp/problem/jump_on_tree

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "tree/hld.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    auto sc = fast_input::Scanner(stdin);

    int N, Q;
    sc >> N >> Q;

    auto hld = HLD(N);
    for (int e = 0; e < N - 1; e++) {
        int a, b;
        sc >> a >> b;
        hld.add_edge(a, b);
    }
    hld.build();

    for (int q = 0; q < Q; q++) {
        int s, t, i;
        sc >> s >> t >> i;

        if (auto v = hld.jump(s, t, i); v.has_value()) {
            std::cout << v.value() << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}