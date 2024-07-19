// verification-helper: PROBLEM https://judge.yosupo.jp/problem/factorize

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "number-theory/factor.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	using factor::factorize;
	using fast_input::Scanner;

	auto sc = Scanner(stdin);

	int T;
	sc.read(T);
	while (T--) {
		u64 n;
		sc.read(n);
		auto factors = factorize(n);
		std::ranges::sort(factors);
		std::cout << size(factors);
		for (u64 f : factors) {
			std::cout << ' ' << f;
		}
		std::cout << '\n';
	}

	return 0;
}