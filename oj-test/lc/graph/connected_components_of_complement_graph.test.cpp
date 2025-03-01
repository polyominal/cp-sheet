// verification-helper: PROBLEM https://judge.yosupo.jp/problem/connected_components_of_complement_graph

#include <cmath>
#include "contest/base.hpp"
#include "graph/complement-graph.hpp"
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    auto cg = ComplementGraph(n);
    for (int e = 0; e < m; e++) {
        int a, b;
        cin >> a >> b;
        cg.add_edge(a, b);
    }

    auto comps = Vec<Vec<int>>();
    cg.get_connected([&](const Vec<int>& comp) { comps.push_back(comp); });

    cout << size(comps) << '\n';
    for (const auto& comp : comps) {
        assert(!comp.empty());
        cout << size(comp);
        for (int v : comp) {
            cout << ' ' << v;
        }
        cout << '\n';
    }

    return 0;
}