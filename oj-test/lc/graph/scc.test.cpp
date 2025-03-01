// verification-helper: PROBLEM https://judge.yosupo.jp/problem/scc

#include "graph/scc.hpp"
#include "data-structure/flatten-vector.hpp"

int main() {
    using namespace std;

    int n, m;
    cin >> n >> m;
    auto edges = Vec<pair<int, int>>(m);
    for (auto& [a, b] : edges) {
        cin >> a >> b;
    }
    auto g = FlattenVector<int>(n, edges);

    auto group_edges = Vec<pair<int, int>>();
    group_edges.reserve(n);
    int cur_idx = 0;
    int num_groups = get_scc(g, [&](const Vec<int>& comp) {
        for (int v : comp) {
            group_edges.emplace_back(cur_idx, v);
        }
        cur_idx++;
    });
    auto groups = FlattenVector<int>(num_groups, group_edges);

    cout << num_groups << '\n';
    for (int z = 0; z < num_groups; z++) {
        const auto& group = groups[z];
        cout << group.size();
        for (int v : group) {
            cout << ' ' << v;
        }
        cout << '\n';
    }

    return 0;
}