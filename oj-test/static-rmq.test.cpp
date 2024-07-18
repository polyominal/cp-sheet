// verification-helper: PROBLEM https://judge.yosupo.jp/problem/staticrmq

#include "contest/base.hpp"
#include "data-structure/static-range.hpp"

using std::cin, std::cout;

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	using T = u32;

	auto A = Vec<T>(N);
	for (auto& a : A) {
		cin >> a;
	}

	auto sr = StaticRange(
		A, [](T a, T b) -> T { return min(a, b); }, T(1.1e9));

	for (int q = 0; q < Q; q++) {
		int l, r;
		cin >> l >> r;
		cout << sr(l, r) << '\n';
	}

	return 0;
}