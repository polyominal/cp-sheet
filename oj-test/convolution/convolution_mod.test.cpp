// verification-helper: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include "algebra/modint.hpp"
#include "algebra/nft.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"

using fast_input::Scanner;

int main() {
	using namespace std;

	auto sc = Scanner();

	using Z = ModInt<998244353>;

	int n, m;
	sc >> n >> m;
	auto a = Vec<Z>(n);
	for (auto& v : a) {
		sc >> v.v;
	}
	auto b = Vec<Z>(m);
	for (auto& v : b) {
		sc >> v.v;
	}

	auto c = multiply(a, b);
	for (ssize_t i = 0; i < ssize(c); i++) {
		cout << c[i].v << " \n"[i == ssize(c) - 1];
	}

	return 0;
}