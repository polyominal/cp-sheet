// verification-helper: PROBLEM https://judge.yosupo.jp/problem/enumerate_triangles

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "graph/enumerate-triangles.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = fast_input::Scanner(stdin);

	int N, M;
	sc >> N >> M;

	auto X = Vec<u32>(N);
	for (auto& x : X) {
		sc >> x;
	}

	auto edges = Vec<pair<int, int>>(M);
	for (auto& [a, b] : edges) {
		sc >> a >> b;
	}

	auto tot = u128(0);
	triangles(N, edges, [&](int x, int y, int z) -> void {
		tot += u128(X[x]) * X[y] * X[z];
	});
	constexpr u32 MOD = 998244353;
	tot %= MOD;
	std::cout << u32(tot) << '\n';

	return 0;
}