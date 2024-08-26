// verification-helper: PROBLEM https://judge.yosupo.jp/problem/tree_path_composite_sum

#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/flatten-vector.hpp"
#include "tree/tree-dp.hpp"

using std::cout;

int main() {
	using fast_input::Scanner;
	auto sc = Scanner(stdin);

	int N;
	sc >> N;

	using Z = ModInt<998244353>;
	auto A = Vec<Z>(N);
	for (auto& a : A) {
		sc >> a.v;
	}

	auto B = Vec<Z>(N - 1);
	auto C = Vec<Z>(N - 1);
	auto edges = Vec<pair<int, int>>();
	edges.reserve(2 * (N - 1));
	for (int e = 0; e < N - 1; e++) {
		int u, v;
		sc >> u >> v >> B[e].v >> C[e].v;
		edges.emplace_back(u, e);
		edges.emplace_back(v, e);
	}
	auto adj = FlattenVector<int>(N, edges);

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