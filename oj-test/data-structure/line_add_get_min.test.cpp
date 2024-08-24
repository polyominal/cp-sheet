// verification-helper: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min

#include <ios>
#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/line-container.hpp"

using fast_input::Scanner;
using line_container::LineContainer;
using std::cout;

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = Scanner();

	int N, Q;
	sc >> N >> Q;
	auto lc = LineContainer();
	for (int i = 0; i < N; i++) {
		i64 a, b;
		sc >> a >> b;
		lc.add(-a, -b);
	}

	while (Q--) {
		int t;
		sc >> t;
		if (t == 0) {
			i64 a, b;
			sc >> a >> b;
			lc.add(-a, -b);
		} else if (t == 1) {
			i64 x;
			sc >> x;
			i64 y = -lc.query(x);
			cout << y << '\n';
		}
	}

	return 0;
}