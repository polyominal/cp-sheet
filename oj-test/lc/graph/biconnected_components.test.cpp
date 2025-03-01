// verification-helper: PROBLEM https://judge.yosupo.jp/problem/biconnected_components

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/flatten-vector.hpp"
#include "graph/block-cut.hpp"

int main() {
    using namespace std;
    using fast_input::Scanner;

    auto sc = Scanner();

    int n, m;
    sc >> n >> m;
    auto edges = Vec<pair<int, int>>(m);
    for (auto& [a, b] : edges) {
        sc >> a >> b;
    }
    edges.resize(2 * m);
    for (int i = 0; i < m; i++) {
        auto [a, b] = edges[i];
        edges[m + i] = {b, a};
    }
    auto g = FlattenVector<int>(n, edges);

    auto bct_edges = Vec<pair<int, int>>();
    int nb =
        block_cut_tree(g, [&](int t, int v) { bct_edges.emplace_back(t, v); });
    auto bct_groups = FlattenVector<int>(nb, bct_edges);

    cout << nb << '\n';
    for (int b = 0; b < nb; b++) {
        cout << size(bct_groups[b]);
        for (int v : bct_groups[b]) {
            cout << ' ' << v;
        }
        cout << '\n';
    }

    return 0;
}