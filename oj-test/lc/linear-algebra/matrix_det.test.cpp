// verification-helper: PROBLEM https://judge.yosupo.jp/problem/matrix_det

#include "algebra/matrix.hpp"
#include "algebra/modint.hpp"

int main() {
    using namespace std;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    using Z = ModInt<998244353>;

    int n;
    cin >> n;
    auto a = Vec<Vec<Z>>(n, Vec<Z>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j].v;
        }
    }

    auto det = matrix::mat_det(a);
    cout << det.v << '\n';

    return 0;
}