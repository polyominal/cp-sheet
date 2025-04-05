// verification-helper: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B

#include "graph/mcmf.hpp"

int main() {
    using namespace std;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, f;
    cin >> n >> m >> f;

    struct E {
        int to;
        int rev;
        int cap;
        int dist;
    };
    auto g = Vec<Vec<E>>(n);
    auto add_edge = [&](int from, int to, int cap, int dist) {
        g[from].push_back({to, int(g[to].size()), cap, dist});
        g[to].push_back({from, int(g[from].size()) - 1, 0, -dist});
    };

    for (int _ = 0; _ < m; _++) {
        int from, to, cap, dist;
        cin >> from >> to >> cap >> dist;
        add_edge(from, to, cap, dist);
    }

    auto mcf = get_mcf<int, int, E>(g, 0, n - 1);
    mcf.max_flow(f);
    if (mcf.tot_flow == f) {
        cout << mcf.tot_cost << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}