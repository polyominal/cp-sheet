// verification-helper: PROBLEM https://judge.yosupo.jp/problem/two_sat

#include "contest/fast-input.hpp"
#include "graph/two-sat.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	using fast_input::Scanner;
	auto sc = Scanner(stdin);

	{
		string dummy;
		sc >> dummy >> dummy;
	}
	int N, M;
	sc >> N >> M;

	auto ts = TwoSat(N);
	auto map_idx = [&](int i) -> int {
		if (i > 0) {
			return i - 1;
		} else if (i < 0) {
			return ~(-i - 1);
		} else {
			assert(false);
		}
	};
	for (int k = 0; k < M; k++) {
		int a, b;
		int dummy;
		sc >> a >> b >> dummy;
		ts.either(map_idx(a), map_idx(b));
	}

	if (auto res = ts.solve(); res.has_value()) {
		std::cout << "s SATISFIABLE" << '\n';
		const auto& sol = res.value();
		std::cout << "v ";
		for (int i = 0; i < N; i++) {
			std::cout << ' ';
			std::cout << (sol[i] ? i + 1 : -(i + 1));
		}
		std::cout << " 0" << '\n';
	} else {
		std::cout << "s UNSATISFIABLE" << '\n';
	}

	return 0;
}