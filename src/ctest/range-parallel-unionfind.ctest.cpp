#include <catch2/catch_test_macros.hpp>

#include "contest/base.hpp"
#include "data-structure/range-parallel-unionfind.hpp"

TEST_CASE("Range parallel union find example", "[range-parallel-unionfind]") {
	// Testcase copied from https://judge.yosupo.jp/problem/range_parallel_unionfind
	auto X = Vec<u64>{12, 34, 56, 78, 90};
	int N = int(size(X));
	u64 tot = 0;
	auto rpuf = RangeParallelUnionFind(N, [&](int a, int b) {
		tot += X[a] * X[b];
		X[a] += X[b];
	});

	rpuf.unite(0, 0, 0);
	REQUIRE(tot == 0);

	rpuf.unite(0, 0, 1);
	REQUIRE(tot == 0);

	rpuf.unite(0, 2, 1);
	REQUIRE(tot == 672);

	rpuf.unite(2, 1, 2);
	REQUIRE(tot == 10940);

	rpuf.unite(0, 1, 2);
	REQUIRE(tot == 10940);

	rpuf.unite(0, 0, 4);
	REQUIRE(tot == 10940);

	rpuf.unite(2, 1, 3);
	REQUIRE(tot == 27140);
}