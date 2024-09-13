// verification-helper: PROBLEM https://judge.yosupo.jp/problem/sum_of_floor_of_linear

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
		cout << scary_prod(N, A, B, M, Sum(), Sum(1, 0, 0), Sum(0, 1, 0)).res
			 << '\n';
	}

	return 0;
}