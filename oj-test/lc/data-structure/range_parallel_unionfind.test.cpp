// verification-helper: PROBLEM https://judge.yosupo.jp/problem/range_parallel_unionfind

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/range-parallel-unionfind.hpp"
#include "data-structure/unionfind.hpp"

using std::cin, std::cout;

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	using fast_input::Scanner;
	auto sc = Scanner();

	int N, Q;
	sc >> N >> Q;

	auto X = Vec<u32>(N);
	for (auto& x : X) {
		sc >> x;
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
		sc >> k >> a >> b;
		rpuf.unite(a, b, k);
		cout << tot << '\n';
	}

	return 0;
}