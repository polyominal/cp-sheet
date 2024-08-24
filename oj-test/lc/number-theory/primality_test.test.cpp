// verification-helper: PROBLEM https://judge.yosupo.jp/problem/primality_test

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "number-theory/factor.hpp"

int main() {
	using factor::is_prime;
	using fast_input::Scanner;

	auto sc = Scanner(stdin);

	int T;
	sc >> T;

	while (T--) {
		u64 n;
		sc >> n;
		if (is_prime(n)) {
			std::cout << "Yes" << '\n';
		} else {
			std::cout << "No" << '\n';
		}
	}

	return 0;
}
