#include "number-theory/multiplicative-eval.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace testing {

TEST(TestMultiplicativeEvaluation, TotientFunction) {
	auto phi = multiplicative_eval<i64>(
		21,
		[](int p, int k) -> i64 {
			assert(k >= 1);
			i64 a = p, b = 1;
			for (int z = 0; z < k - 1; z++) {
				a *= p, b *= p;
			}
			return a - b;
		},
		std::multiplies<i64>());
	EXPECT_THAT(Vec<i64>(begin(phi) + 1, end(phi)),
				ElementsAre(1, 1, 2, 2, 4, 2, 6, 4, 6, 4, 10, 4, 12, 6, 8, 8,
							16, 6, 18, 8, 12));
}

}  // namespace testing