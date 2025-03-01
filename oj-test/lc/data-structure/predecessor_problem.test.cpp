// verification-helper: PROBLEM https://judge.yosupo.jp/problem/predecessor_problem

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/fast-set.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    using fast_input::Scanner;
    auto sc = Scanner();

    int N, Q;
    sc >> N >> Q;
    auto fs = FastSet(N);

    {
        string T;
        sc >> T;
        for (int i = 0; i < N; i++) {
            if (T[i] == '1') {
                fs.set(i);
            }
        }
    }

    while (Q--) {
        int t, k;
        sc >> t >> k;

        using std::cout;

        if (t == 0) {
            fs.set(k);
        } else if (t == 1) {
            fs.reset(k);
        } else if (t == 2) {
            cout << (fs[k] ? '1' : '0') << '\n';
        } else if (t == 3) {
            if (auto res = fs.next(k); res < N) {
                cout << res << '\n';
            } else {
                cout << -1 << '\n';
            }
        } else if (t == 4) {
            if (auto res = fs.prev(k); res >= 0) {
                cout << res << '\n';
            } else {
                cout << -1 << '\n';
            }
        } else {
            assert(false);
        }
    }

    return 0;
}