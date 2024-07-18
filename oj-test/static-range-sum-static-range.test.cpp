// verification-helper: PROBLEM https://judge.yosupo.jp/problem/static_range_sum

#include "data-structure/static-range.hpp"
#include "contest/base.hpp"

using std::cin, std::cout;

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	using T = u64;

	auto A = Vec<T>(N);
	for (auto& a : A) {
		cin >> a;
	}

	auto sr = StaticRange(
		A, [](T a, T b) -> T { return a + b; }, T(0));

	for (int q = 0; q < Q; q++) {
		int l, r;
		cin >> l >> r;
		cout << sr(l, r) << '\n';
	}

	return 0;
}