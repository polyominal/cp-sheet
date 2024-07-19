// verification-helper: PROBLEM https://judge.yosupo.jp/problem/kth_root_integer

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "number-theory/int-kth-root.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = fast_input::Scanner(stdin);

	int T;
	sc.read(T);
	while (T--) {
		u64 a, k;
		sc.read(a, k);
		std::cout << int_kth_root(a, k) << '\n';
	}

	return 0;
}