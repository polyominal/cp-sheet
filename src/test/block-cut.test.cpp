#include <catch2/catch_test_macros.hpp>

#include "contest/base.hpp"
#include "graph/block-cut.hpp"

TEST_CASE("Block-cut tree: simple", "[block-cut]") {
	{
		int N = 1;
		VV<int> adj(N);
		auto tr = block_cut_tree(N, adj);
		REQUIRE(tr.size() == 2);
		REQUIRE(tr[0] == V<int>{1});
		REQUIRE(tr[1] == V<int>{0});
	}

	{
		int N = 2;
		VV<int> adj(N);
		adj[0].push_back(1);
		adj[1].push_back(0);
		auto tr = block_cut_tree(N, adj);
		REQUIRE(tr.size() == 3);
	}

	{
		int N = 4;
		VV<int> adj(N);
		auto add_edge = [&](int a, int b) -> void {
			adj[a].push_back(b);
			adj[b].push_back(a);
		};
		using P = pair<int, int>;
		for (auto [a, b] : V<P>{P(0,3), P(0,1), P(3,0), P(2,1), P(2,3)}) {
			add_edge(a, b);
		}

		auto tr = block_cut_tree(N, adj);
		REQUIRE(tr.size() == 5);
		REQUIRE(tr.back().size() == 4);
		for (int i = 0; i < N; i++) {
			REQUIRE(tr[i].size() == 1);
		}
	}
}