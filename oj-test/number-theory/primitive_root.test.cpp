// verification-helper: PROBLEM https://judge.yosupo.jp/problem/primitive_root

#include "contest/base.hpp"
#include "number-theory/factor.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	int Q;
	std::cin >> Q;

	using factor::primitive_root;

	while (Q--) {
		u64 p;
		std::cin >> p;
		std::cout << primitive_root(p) << '\n';
	}

	return 0;
}
