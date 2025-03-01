// verification-helper: PROBLEM https://judge.yosupo.jp/problem/matrix_rank

#include "algebra/matrix.hpp"
#include "algebra/modint.hpp"

int main() {
    using namespace std;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    using Z = ModInt<998244353>;

    int n, m;
    cin >> n >> m;
    auto a = Vec<Vec<Z>>(n, Vec<Z>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j].v;
        }
    }

    int r = matrix::mat_rank(a);
    cout << r << '\n';

    return 0;
}