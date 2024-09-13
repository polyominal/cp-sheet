// verification-helper: PROBLEM https://judge.yosupo.jp/problem/min_of_mod_of_linear

#include "ad-hoc/scary-product.hpp"

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		i64 N, M, A, B;
		cin >> N >> M >> A >> B;
		cout << B + scary_prod(N, A, B, M, MinMod(), MinMod(A, 0),
							   MinMod(-M, MinMod::INF))
						.best
			 << '\n';
	}

	return 0;
}