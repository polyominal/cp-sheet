#include <gtest/gtest.h>
#include <algebra/matrix.hpp>
#include <algebra/modint.hpp>
#include <util/random.hpp>

namespace testing {

TEST(TestMatrix, TestInverseModuloPrime) {
	auto rng = Random(1234);

	for (int N : {1, 5, 10, 55, 88}) {
		constexpr uint32_t mod = uint32_t(1e9) + 7;
		using Z = ModInt<mod>;
		Vec<Vec<Z>> A(N, Vec<Z>(N));
		while (true) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					A[i][j].v = rng.uniform<uint32_t>(0, mod - 1);
				}
			}
			auto iA = matrix::mat_inv(A);
			if (!iA.empty()) {
				for (int z = 0; z < 2; z++) {
					Vec<Vec<Z>> prod(N, Vec<Z>(N));
					for (int i = 0; i < N; i++) {
						for (int k = 0; k < N; k++) {
							Z v = A[i][k];
							if (v == Z(0)) continue;
							for (int j = 0; j < N; j++) {
								prod[i][j] += v * iA[k][j];
							}
						}
					}
					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							EXPECT_EQ(prod[i][j], Z(i == j));
						}
					}
					swap(A, iA);
				}
				break;
			}
		}
	}
}

TEST(TestMatrix, TestEquationModuloPrime) {
	auto rng = Random(1234);

	for (int N : {1, 5, 10, 55, 88}) {
		constexpr uint32_t mod = uint32_t(1e9) + 7;
		using Z = ModInt<mod>;
		Vec<Vec<Z>> A(N, Vec<Z>(N));
		Vec<Z> b(N);
		while (true) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					A[i][j].v = rng.uniform<uint32_t>(0, mod - 1);
				}
			}
			if (matrix::mat_det(A) == Z(0)) continue;

			for (int j = 0; j < N; j++) {
				b[j].v = rng.uniform<uint32_t>(0, mod - 1);
			}
			auto [x, kernel] = matrix::solve_lineareq(A, b);
			assert(kernel.empty());
			for (int i = 0; i < N; i++) {
				Z res = 0;
				for (int j = 0; j < N; j++) {
					res += A[i][j] * x[j];
				}
				EXPECT_EQ(res, b[i]);
			}
			break;
		}
	}
}

}  // namespace testing