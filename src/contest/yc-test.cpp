#include <gtest/gtest.h>
#include <contest/yc.hpp>

namespace testing {

TEST(TestYCombinator, Example) {
	// gcd(a, b)
	EXPECT_EQ(std::y_combinator([](auto self, int a, int b) -> int {
				  if (b == 0) {
					  return a;
				  }
				  return self(b, a % b);
			  })(12, 8),
			  4);
}

}  // namespace testing