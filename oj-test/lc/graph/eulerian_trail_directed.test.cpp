// verification-helper: PROBLEM https://judge.yosupo.jp/problem/eulerian_trail_directed

#include "contest/base.hpp"
#include "graph/eulerian-trail.hpp"

using eulerian_trail::trail_directed;

int main() {
    using namespace std;

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;

        auto edges = Vec<pair<int, int>>(M);
        for (auto& [a, b] : edges) {
            cin >> a >> b;
        }

        if (auto res = trail_directed(N, edges); res.has_value()) {
            auto trail = res.value();
            assert(int(size(trail)) == M + 1);

            cout << "Yes" << '\n';
            for (ssize_t z = 0; z < ssize(trail); z++) {
                int v = trail[z].first;
                cout << v << " \n"[z + 1 == ssize(trail)];
            }
            for (ssize_t z = 1; z < ssize(trail); z++) {
                int e = trail[z].second;
                cout << e << " \n"[z + 1 == ssize(trail)];
            }
        } else {
            cout << "No" << '\n';
        }
    }

    return 0;
}