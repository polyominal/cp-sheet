#include <catch2/catch_test_macros.hpp>

#include "graph/enumerate-triangles.hpp"

#include "util/random.hpp"

TEST_CASE("Triangle enumeration", "[enumerate-triangles]") {
	auto rng = Random(1145141);

	for (int N : {2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		VV<bool> adj(N, V<bool>(N));
		V<pair<int, int>> edges;
		for (int a = 0; a < N; a++) {
			for (int b = a+1; b < N; b++) {
				if (rng.uniform(0, 9) < 7) {
					adj[a][b] = adj[b][a] = true;
					edges.emplace_back(a, b);
				}
			}
		}

		V<tuple<int, int, int>> res;
		triangles(N, edges, [&](int x, int y, int z) -> void {
			if (x > y) swap(x, y);
			if (x > z) swap(x, z);
			if (y > z) swap(y, z);
			res.emplace_back(x, y, z);
		});
		sort(res.begin(), res.end());

		V<tuple<int, int, int>> res_naive;
		for (int x = 0; x < N; x++) {
			for (int y = x+1; y < N; y++) {
				for (int z = y+1; z < N; z++) {
					if (adj[x][y] && adj[y][z] && adj[z][x]) {
						res_naive.emplace_back(x, y, z);
					}
				}
			}
		}

		REQUIRE(res == res_naive);
	}
}
