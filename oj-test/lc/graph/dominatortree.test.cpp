// verification-helper: PROBLEM https://judge.yosupo.jp/problem/dominatortree

#include "data-structure/flatten-vector.hpp"
#include "graph/dominator.hpp"

int main() {
    using namespace std;

    int n, m, s;
    cin >> n >> m >> s;
    auto edges = Vec<pair<int, int>>(m);
    for (auto& [a, b] : edges) {
        cin >> a >> b;
    }

    auto g = FlattenVector<int>(n, edges);
    auto idom = build_idom(n, g, s);
    idom[s] = s;
    for (int i = 0; i < n; i++) {
        cout << idom[i] << " \n"[i + 1 == n];
    }

    return 0;
}