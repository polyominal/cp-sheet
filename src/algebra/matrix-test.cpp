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
			auto [x, kernel] = matrix::solve_lineareq(A, b).value();
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

TEST(TestMatrix, TestKernel) {
	auto rng = Random(20240909);
	constexpr u32 mod = 998244353;
	using Z = ModInt<mod>;
	for (int ncase = 0; ncase < 20; ncase++) {
		int n = rng.uniform(1, 30);
		int m = rng.uniform(1, 30);
		auto a = Vec<Vec<Z>>(n, Vec<Z>(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				a[i][j] = Z(rng.uniform<u32>(0, mod - 1));
			}
		}
		auto [x, kernel] = matrix::solve_lineareq(a, Vec<Z>(n, Z(0))).value();

		for (int z = 0; z < 10; z++) {
			auto p = x;
			for (const auto& k : kernel) {
				auto c = Z(rng.uniform<u32>(0, mod - 1));
				for (int j = 0; j < m; j++) {
					p[j] += c * k[j];
				}
			}

			auto y = Vec<Z>(n, Z(0));
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					y[i] += a[i][j] * p[j];
				}
			}
			EXPECT_EQ(y, Vec<Z>(n, Z(0)));
		}
	}
}

}  // namespace testing