#include <gtest/gtest.h>
#include <contest/base.hpp>
#include <graph/enumerate-triangles.hpp>
#include <util/random.hpp>

namespace testing {

TEST(EnumerateTrianglesTest, Random) {
	auto rng = Random(1145141);

	for (int N : {2, 3, 5, 8, 13, 21, 34}) {
		auto adj = Vec<Vec<bool>>(N, Vec<bool>(N));
		auto edges = Vec<pair<int, int>>();
		for (int a = 0; a < N; a++) {
			for (int b = a + 1; b < N; b++) {
				if (rng.uniform(0, 9) < 7) {
					adj[a][b] = adj[b][a] = true;
					edges.emplace_back(a, b);
				}
			}
		}

		auto res = Vec<tuple<int, int, int>>();
		triangles(N, edges, [&](int x, int y, int z) -> void {
			if (x > y) swap(x, y);
			if (x > z) swap(x, z);
			if (y > z) swap(y, z);
			res.emplace_back(x, y, z);
		});
		std::ranges::sort(res);

		auto res_naive = Vec<tuple<int, int, int>>();
		for (int x = 0; x < N; x++) {
			for (int y = x + 1; y < N; y++) {
				for (int z = y + 1; z < N; z++) {
					if (adj[x][y] && adj[y][z] && adj[z][x]) {
						res_naive.emplace_back(x, y, z);
					}
				}
			}
		}

		EXPECT_EQ(res, res_naive);
	}
}

}  // namespace testing