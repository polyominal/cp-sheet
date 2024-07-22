#include <gtest/gtest.h>
#include <ad-hoc/tree-dp.hpp>
#include <algebra/modint.hpp>
#include <util/random.hpp>

TEST(TreeDPTest, TreePathCompositeSum) {
	auto rng = Random(20240725);
	for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		auto tr = Vec<Vec<int>>(N);
		auto edges = Vec<int>(N - 1);
		for (int v = 1; v < N; v++) {
			int w = rng.uniform(0, v - 1);
			int e = v - 1;
			tr[v].push_back(e);
			tr[w].push_back(e);
			edges[e] = v ^ w;
		}

		constexpr u32 MOD = 998244353;
		using Z = ModInt<MOD>;
		auto A = Vec<Z>(N);
		for (int v = 0; v < N; v++) {
			A[v].v = rng.uniform<u32>(0, MOD - 1);
		}
		auto B = Vec<Z>(N - 1);
		auto C = Vec<Z>(N - 1);
		for (int e = 0; e < N - 1; e++) {
			B[e].v = rng.uniform<u32>(0, MOD - 1);
			C[e].v = rng.uniform<u32>(0, MOD - 1);
		}

		using S = array<Z, 2>;	// [0]: sum; [1]: count
		auto make = [&](int v) -> S { return S{A[v], 1}; };
		auto rake = [&](const S& a, const S& b, int) -> S {
			return S{a[0] + b[0], a[1] + b[1]};
		};
		auto compress = [&](const S& a, int e, int) -> S {
			return S{a[0] * B[e] + a[1] * C[e], a[1]};
		};

		auto tdp = TreeDP<S>::solve(tr, make, rake, compress);

		for (int root = 0; root < N; root++) {
			auto dfs = [&](auto self, int v, int p) -> S {
				S res = make(v);
				for (int e : tr[v]) {
					// Skip the parent edge
					if (e == p) continue;
					int w = v ^ edges[e];
					S w_res = self(self, w, e);
					res[0] += w_res[0] * B[e] + w_res[1] * C[e];
					res[1] += w_res[1];
				}
				return res;
			};
			EXPECT_EQ(tdp.get_vertex(root), dfs(dfs, root, -1));
		}
	}
}