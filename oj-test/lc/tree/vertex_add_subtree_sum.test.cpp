// verification-helper: PROBLEM https://judge.yosupo.jp/problem/vertex_add_subtree_sum

#include "contest/base.hpp"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    auto A = Vec<i64>(N);
    for (i64& a : A) {
        cin >> a;
    }

    auto ch = Vec<Vec<int>>(N);
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        ch[p].push_back(i);
    }

    auto iord = Vec<int>(N);
    auto sz = Vec<int>(N, 1);

    {
        auto ord = Vec<int>();
        ord.reserve(N);
        auto stk = Vec<int>{0};
        stk.reserve(N);
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();

            int i = int(size(ord));
            ord.push_back(v);
            iord[v] = i;

            for (int w : ch[v]) {
                stk.push_back(w);
            }
        }

        for (int v : ord | std::views::reverse) {
            for (int w : ch[v]) {
                sz[v] += sz[w];
            }
        }
        assert(sz[0] == N);
    }

    const int S = int(bit_ceil<u32>(N));
    auto seg = Vec<i64>(2 * S);
    auto update = [&](int a) -> void {
        assert(a < S);
        seg[a] = seg[2 * a] + seg[2 * a + 1];
    };

    for (int v = 0; v < N; v++) {
        seg[S + iord[v]] = A[v];
    }
    for (int a = S - 1; a >= 1; a--) {
        update(a);
    }

    while (Q--) {
        int t, v;
        cin >> t >> v;
        if (t == 0) {
            i64 x;
            cin >> x;
            for (int a = S + iord[v]; a >= 1; a /= 2) {
                seg[a] += x;
            }
        } else if (t == 1) {
            int l = iord[v];
            int r = iord[v] + sz[v];
            i64 res = 0;
            for (int a = S + l, b = S + r; a < b; a /= 2, b /= 2) {
                if (a & 1) {
                    res += seg[a++];
                }
                if (b & 1) {
                    res += seg[--b];
                }
            }
            std::cout << res << '\n';
        } else {
            assert(false);
        }
    }

    return 0;
}