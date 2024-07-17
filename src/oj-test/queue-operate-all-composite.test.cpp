// verification-helper: PROBLEM https://judge.yosupo.jp/problem/queue_operate_all_composite

#include "contest/base.hpp"
#include "algebra/modint.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/queue-aggregation.hpp"

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = fast_input::Scanner(stdin);

	int Q;
	sc.read(Q);

	using Z = ModInt<998244353>;
	using F = pair<Z, Z>;

	auto qa = QueueAggregation([](const F& f, const F& g) -> F {
		return {f.first * g.first, f.second * g.first + g.second};
	}, F{1, 0});

	for (int q = 0; q < Q; q++) {
		int t;
		sc.read(t);

		if (t == 0) {
			F f;
			sc.read(f.first.v, f.second.v);
			qa.push(f);
		} else if (t == 1) {
			qa.pop();
		} else if (t == 2) {
			Z x;
			sc.read(x.v);
			F prod = qa.prod();
			std::cout << (prod.first * x + prod.second).v << '\n';
		} else assert(false);
	}

	return 0;
}