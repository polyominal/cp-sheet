#include <catch2/catch_test_macros.hpp>

#include "algebra/matrix.hpp"
#include "algebra/modint.hpp"

#include "util/random.hpp"

namespace matrix {

template <uint32_t mod> F_zero<modint<mod>> f_zero  = [](modint<mod> a) -> bool {
	return a.v == 0;
};
template <uint32_t mod> F_better<modint<mod>> f_better = [](modint<mod> a, modint<mod>) -> bool {
	return !f_zero<mod>(a);
};

TEST_CASE("Matrix inverse modulo prime", "[matrix]") {
	auto rng = Random(1234);

	for (int N : {1, 5, 10, 55, 88}) {
		constexpr uint32_t mod = uint32_t(1e9) + 7;
		using num = modint<mod>;
		Vec<Vec<num>> A(N, Vec<num>(N));
		while (true) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					A[i][j].v = rng.uniform<uint32_t>(0, mod-1);
				}
			}
			auto iA = mat_inv(A, f_better<mod>, f_zero<mod>);
			if (!iA.empty()) {
				for (int z = 0; z < 2; z++) {
					Vec<Vec<num>> prod(N, Vec<num>(N));
					for (int i = 0; i < N; i++) {
						for (int k = 0; k < N; k++) {
							num v = A[i][k];
							if (f_zero<mod>(v)) continue;
							for (int j = 0; j < N; j++) {
								prod[i][j] += v * iA[k][j];
							}
						}
					}
					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							REQUIRE(prod[i][j] == num(i == j));
						}
					}
					swap(A, iA);
				}
				break;
			}
		}
	}
}

TEST_CASE("Matrix equation modulo prime", "[matrix]") {
	auto rng = Random(1234);

	for (int N : {1, 5, 10, 55, 88}) {
		constexpr uint32_t mod = uint32_t(1e9) + 7;
		using num = modint<mod>;
		Vec<Vec<num>> A(N, Vec<num>(N));
		Vec<num> b(N);
		while (true) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					A[i][j].v = rng.uniform<uint32_t>(0, mod-1);
				}
			}
			if (mat_det(A, f_better<mod>, f_zero<mod>).v == 0) continue;

			for (int j = 0; j < N; j++) {
				b[j].v = rng.uniform<uint32_t>(0, mod-1);
			}
			// How to verify kernel vectors?
			auto x = solve_lineareq(A, b, f_better<mod>, f_zero<mod>).first;
			for (int i = 0; i < N; i++) {
				num res = 0;
				for (int j = 0; j < N; j++) {
					res += A[i][j] * x[j];
				}
				REQUIRE(res == b[i]);
			}
			break;
		}
	}
}

} // namespace matrix