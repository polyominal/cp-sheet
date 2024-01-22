#include <catch2/catch_test_macros.hpp>

#include "graph/hld.hpp"

#include "util/random.hpp"

// TODO: Generate "uniform" random trees
V<int> get_random_tree_stupid(int N) {
	static auto rng = Random(20240106);
	V<int> par(N);
	par[0] = -1;
	for (int i = 1; i < N; i++) {
		par[i] = rng.uniform<int>(0, i-1);
	}
	return par;
}

TEST_CASE("HLD: tree compression", "[hld]") {
	V<int> par = {2, 2, -1, 0, 1, 0};
	HLD hld(par);
	REQUIRE(hld.compress({1, 0}) == make_pair(V<int>{2, 0, 1}, V<int>{-1, 0, 0}));
	REQUIRE(hld.compress({5, 3}) == make_pair(V<int>{0, 3, 5}, V<int>{-1, 0, 0}));
	REQUIRE(hld.compress({5, 3, 4}) == make_pair(V<int>{2, 0, 3, 5, 4}, V<int>{-1, 0, 1, 1, 0}));
	REQUIRE(hld.compress({5, 0, 2}) == make_pair(V<int>{2, 0, 5}, V<int>{-1, 0, 1}));
}

TEST_CASE("HLD (par_i < i): lca, get_ancestor and get_lowest", "[hld]") {
	for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		auto par = get_random_tree_stupid(N);
		V<int> depth(N);
		depth[0] = 0;
		for (int i = 1; i < N; i++) {
			depth[i] = depth[par[i]] + 1;
		}

		HLD hld(par);

		auto lca_naive = [&](int a, int b) -> int {
			if (depth[a] < depth[b]) {
				swap(a, b);
			}
			while (depth[a] > depth[b]) {
				a = par[a];
			}
			while (a != b) {
				a = par[a], b = par[b];
			}
			return a;
		};
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				REQUIRE(hld.lca(i, j) == lca_naive(i, j));
			}
		}

		auto kth_ancestor_naive = [&](int a, int k) -> int {
			if (k > depth[a]) return -1;
			while (k--) {
				a = par[a];
			}
			return a;
		};
		for (int i = 0; i < N; i++) {
			for (int k = 0; k <= N; k++) {
				REQUIRE(hld.get_ancestor(i, k) == kth_ancestor_naive(i, k));
			}
		}

		for (int i = 0; i < N; i++) {
			for (int k = 0; k <= depth[i]; k++) {
				REQUIRE(kth_ancestor_naive(i, k) == hld.get_lowest(i, [&](int j) -> bool {
					return depth[j] <= depth[i]-k;
				}));
			}
		}

		auto in_subtree_naive = [&](int a, int v) -> bool {
			return lca_naive(a, v) == a;
		};
		for (int a = 0; a < N; a++) {
			for (int v = 0; v < N; v++) {
				REQUIRE(hld.in_subtree(a, v) == in_subtree_naive(a, v));
			}
		}
	}
}