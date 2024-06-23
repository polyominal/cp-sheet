#include <catch2/catch_test_macros.hpp>

#include "contest/base.hpp"
#include "algebra/modint.hpp"
#include "data-structure/assignment-segtree.hpp"
#include "util/random.hpp"

TEST_CASE("Assignment segtree: affine") {
	auto rng = Random(20240130);

	const uint32_t mod = uint32_t(1e9) + 7;
	using num = modint<mod>;

	struct Monoid {
		using S = pair<num, num>;

		constexpr S e() { return S(1, 0); }
		S op(S f, S g) {
			return {f.first * g.first, f.second * g.first + g.second};
		}
	} m;
	using S = Monoid::S;

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
		auto uniform_affine = [&]() -> S {
			return S(rng.uniform<uint32_t>(0, mod - 1),
					rng.uniform<uint32_t>(0, mod - 1));
		};
		Vec<S> A(N);
		for (S& a : A) a = uniform_affine();

		auto ast = AssignmentSegtree(N, [&A](int i) {
			return A[i];
		}, m);

		constexpr int Q = 20;
		for (int q = 0; q < Q; q++) {
			{
				int l, r;
				while (true) {
					l = rng.uniform(0, N);
					r = rng.uniform(0, N);
					if (l <= r) break;
				}
				auto f = uniform_affine();
				for (int i = l; i < r; i++) {
					A[i] = f;
				}
				ast.assign(l, r, f);
			}

			for (int l = 0; l <= N; l++) {
				S prod = m.e();
				for (int r = l; r <= N; r++) {
					REQUIRE(prod == ast.prod(l, r));
					if (r < N) {
						prod = m.op(prod, A[r]);
					}
				}
			}
		}
	}
}