// verification-helper: PROBLEM https://judge.yosupo.jp/problem/tree_path_composite_sum

#include "ad-hoc/tree-dp.hpp"
#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"

using std::cin, std::cout;

int main() {
	using fast_input::Scanner;
	auto sc = Scanner(stdin);

	int N;
	sc.read(N);

	using Z = ModInt<998244353>;
	auto A = Vec<Z>(N);
	for (auto& a : A) sc.read(a.v);

	auto adj = Vec<Vec<int>>(N);
	auto B = Vec<Z>(N - 1);
	auto C = Vec<Z>(N - 1);
	for (int e = 0; e < N - 1; e++) {
		int u, v;
		sc.read(u, v, B[e].v, C[e].v);
		adj[u].push_back(e);
		adj[v].push_back(e);
	}

	using S = array<Z, 2>;	// [0]: sum; [1]: count
	auto make = [&](int v) -> S { return S{A[v], 1}; };
	auto rake = [&](const S& a, const S& b, int) -> S {
		return S{a[0] + b[0], a[1] + b[1]};
	};
	auto compress = [&](const S& a, int e, int) -> S {
		return S{a[0] * B[e] + a[1] * C[e], a[1]};
	};
	auto tdp = TreeDP<S>::solve(adj, make, rake, compress);

	for (int v = 0; v < N; v++) {
		Z res = tdp.get_vertex(v)[0];
		cout << res.v << '\n';
	}

	return 0;
}