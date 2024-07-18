// verification-helper: PROBLEM https://judge.yosupo.jp/problem/enumerate_triangles

#include <contest/base.hpp>
#include <contest/fast-input.hpp>
#include <graph/enumerate-triangles.hpp>
#include <algebra/modint.hpp>

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = fast_input::Scanner(stdin);

	int N, M;
	sc.read(N, M);

	using Z = ModInt<998244353>;

	auto X = Vec<Z>(N);
	for (auto& x : X) {
		sc.read(x.v);
	}

	auto edges = Vec<pair<int, int>>(M);
	for (auto& [a, b] : edges) {
		sc.read(a, b);
	}

	auto tot = Z(0);
	triangles(N, edges, [&](int x, int y, int z) -> void {
		tot += X[x] * X[y] * X[z];
	});

	std::cout << tot.v << '\n';

	return 0;
}