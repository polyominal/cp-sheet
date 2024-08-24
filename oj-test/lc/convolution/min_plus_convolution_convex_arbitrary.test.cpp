// verification-helper: PROBLEM https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary

#include "ad-hoc/min-plus-convex.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"

int main() {
	using fast_input::Scanner;

	std::ios_base::sync_with_stdio(false);

	auto sc = Scanner(stdin);

	int N, M;
	sc >> N >> M;
	auto A = Vec<i64>(N), B = Vec<i64>(M);
	for (i64& a : A) sc >> a;
	for (i64& b : B) sc >> b;

	auto result = min_plus_convex(A, B);
	int len = int(size(result));
	for (int k = 0; k < len; k++) {
		std::cout << result[k] << " \n"[k + 1 == len];
	}

	return 0;
}