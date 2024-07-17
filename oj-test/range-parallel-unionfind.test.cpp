// verification-helper: PROBLEM https://judge.yosupo.jp/problem/range_parallel_unionfind

#include "contest/base.hpp"
#include "data-structure/unionfind.hpp"
#include "data-structure/range-parallel-unionfind.hpp"

using std::cin, std::cout;

int main() {
	int N, Q;
	cin >> N >> Q;

	auto X = Vec<u32>(N);
	for (auto& x : X) {
		cin >> x;
	}

	constexpr u32 MOD = 998244353;
	u32 tot = 0;
	auto rpuf = RangeParallelUnionFind(N, [&](int p, int c) -> void {
		tot += u32(u64(X[p]) * X[c] % MOD);
		if (tot >= MOD) tot -= MOD;
		X[p] += X[c];
		if (X[p] >= MOD) X[p] -= MOD;
	});

	for (int q = 0; q < Q; q++) {
		int k, a, b;
		cin >> k >> a >> b;
		rpuf.unite(a, b, k);
		cout << tot << '\n';
	}

	return 0;
}