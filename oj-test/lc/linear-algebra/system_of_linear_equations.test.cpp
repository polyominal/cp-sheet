// verification-helper: PROBLEM https://judge.yosupo.jp/problem/system_of_linear_equations

#include "algebra/matrix.hpp"
#include "algebra/modint.hpp"
#include "contest/base.hpp"

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

	auto b = Vec<Z>(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i].v;
	}

	// if (auto [x, kernel] = matrix::solve_lineareq(a, b); !x.empty()) {
	if (auto result = matrix::solve_lineareq(a, b); result.has_value()) {
		const auto& [x, kernel] = result.value();
		cout << kernel.size() << '\n';
		for (int j = 0; j < m; j++) {
			cout << x[j].v << " \n"[j + 1 == m];
		}
		for (const auto& v : kernel) {
			for (int j = 0; j < m; j++) {
				cout << v[j].v << " \n"[j + 1 == m];
			}
		}
	} else {
		cout << -1 << '\n';
	}

	return 0;
}