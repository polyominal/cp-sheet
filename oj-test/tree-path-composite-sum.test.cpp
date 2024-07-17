// verification-helper: PROBLEM https://judge.yosupo.jp/problem/tree_path_composite_sum

#include "contest/base.hpp"
#include "ad-hoc/tree-dp.hpp"
#include "algebra/modint.hpp"

using std::cin, std::cout;

int main() {
	int N;
	cin >> N;

	using Z = ModInt<998244353>;
	auto A = Vec<Z>(N);
	for (auto& a : A) cin >> a.v;

	struct E {
		int dest;
		int idx;

		operator int() const {
			return dest;
		}
	};
	auto adj = Vec<Vec<E>>(N);
	auto B = Vec<Z>(N-1);
	auto C = Vec<Z>(N-1);
	for (int e = 0; e < N-1; e++) {
		int u, v;
		cin >> u >> v >> B[e].v >> C[e].v;
		adj[u].push_back(E{v, e});
		adj[v].push_back(E{u, e});
	}

	struct Manager {
		const Vec<Z>& A, B, C;

		struct Result {
			Z top;
			Z s;
			Z c;
		};
		using S = Result;

		S make(int v) {
			return S{A[v], A[v], 1};
		}
		S op(const S& a, const S& b) {
			assert(a.top == b.top);
			return S{a.top, a.s + b.s - a.top, a.c + b.c - 1};
		}
		S up(const S& a, const E& e) {
			return S{A[e.dest], A[e.dest] + a.s * B[e.idx] + a.c * C[e.idx], a.c + 1};
		}
	};

	auto tdp = TreeDP(Manager{.A=A, .B=B, .C=C}, adj);
	for (int i = 0; i < N; i++) {
		cout << tdp[i].s.v << '\n';
	}

	return 0;
}