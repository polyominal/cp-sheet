// verification-helper: PROBLEM https://judge.yosupo.jp/problem/zalgorithm

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "string/z-algorithm.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = fast_input::Scanner(stdin);

	string S;
	sc >> S;
	const int N = int(size(S));

	auto z = z_algo(S);
	for (int i = 0; i < N; i++) {
		std::cout << z[i] << " \n"[i + 1 == N];
	}

	return 0;
}