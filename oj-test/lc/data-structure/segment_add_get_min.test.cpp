// verification-helper: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min

#include "ad-hoc/li-chao-segtree.hpp"
#include "contest/fast-input.hpp"

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    using fast_input::Scanner;
    auto sc = Scanner();

    int N, Q;
    sc >> N >> Q;

    using namespace lichao_impl;

    Node* rt = nullptr;

    for (int i = 0; i < N; i++) {
        int l, r;
        sc >> l >> r;
        i64 a, b;
        sc >> a >> b;
        rt = insert_outer({-a, -b}, rt, LO, HI, l, r);
    }

    for (int q = 0; q < Q; q++) {
        int t;
        sc >> t;
        if (t == 0) {
            int l, r;
            sc >> l >> r;
            i64 a, b;
            sc >> a >> b;
            rt = insert_outer({-a, -b}, rt, LO, HI, l, r);
        } else if (t == 1) {
            int p;
            sc >> p;
            auto res = -point_query(p, rt, LO, HI);
            if (res == INF) {
                cout << "INFINITY" << '\n';
            } else {
                cout << res << '\n';
            }
        } else {
            assert(false);
        }
    }

    return 0;
}