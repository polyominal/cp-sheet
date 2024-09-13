#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <number-theory/extgcd.hpp>

namespace testing {

TEST(TestExtGcd, TestExtGcd) {
	using T = i64;
	constexpr T LIMIT = 100;
	for (T a = -LIMIT; a <= LIMIT; a++) {
		for (T b = -LIMIT; b <= LIMIT; b++) {
			auto [x, y, g] = extgcd(a, b);
			EXPECT_EQ(abs(g), std::gcd(a, b));
			EXPECT_EQ(a * x + b * y, g);
			if (b == 0) {
				EXPECT_EQ(g, a);
				EXPECT_EQ(x, 1);
				EXPECT_EQ(y, 0);
			} else if (a == 0 || abs(a) == abs(b)) {
				EXPECT_EQ(g, b);
				EXPECT_EQ(x, 0);
				EXPECT_EQ(y, 1);
			} else {
				EXPECT_LE(2 * abs(x), abs(b));
				EXPECT_LE(2 * abs(y), abs(a));
			}
		}
	}
}

TEST(TestExtGcd, TestCRT) {
	{
		EXPECT_EQ(crt<int>(13, 6, -1, 10).value(), std::make_pair(19, 30));
		EXPECT_EQ(crt(5, 6, 8, 10), std::nullopt);
	}

	{
		// (a0, m0), (a1, m1)
		using T = i64;
		constexpr T LIMIT = 30;
		for (T m0 = 1; m0 <= LIMIT; m0++) {
			for (T m1 = 1; m1 <= LIMIT; m1++) {
				T l = m0 / std::gcd(m0, m1) * m1;
				auto table = Vec<Vec<Opt<T>>>(m0, Vec<Opt<T>>(m1));
				for (T x = 0; x < l; x++) {
					table[x % m0][x % m1] = x;
				}

				for (T a0 = -LIMIT; a0 <= LIMIT; a0++) {
					for (T a1 = -LIMIT; a1 <= LIMIT; a1++) {
						T a0_fixed = fix(a0, m0);
						T a1_fixed = fix(a1, m1);
						auto res = crt(a0, m0, a1, m1);
						auto expected = table[a0_fixed][a1_fixed];
						if (res.has_value()) {
							EXPECT_EQ(res.value().first, expected.value());
							EXPECT_EQ(res.value().second, l);
						} else {
							EXPECT_FALSE(expected.has_value());
						}
					}
				}
			}
		}
	}

	{
		// (a0, m0), (a1, m1), (a2, m2)
		using T = i64;
		constexpr T LIMIT = 8;
		for (T m0 = 1; m0 <= LIMIT; m0++) {
			for (T m1 = 1; m1 <= LIMIT; m1++) {
				for (T m2 = 1; m2 <= LIMIT; m2++) {
					T l = m0 / std::gcd(m0, m1) * m1;
					l = l / std::gcd(l, m2) * m2;
					auto table = Vec<Vec<Vec<Opt<T>>>>(
						m0, Vec<Vec<Opt<T>>>(m1, Vec<Opt<T>>(m2)));
					for (T x = 0; x < l; x++) {
						table[x % m0][x % m1][x % m2] = x;
					}

					for (T a0 = -LIMIT; a0 <= LIMIT; a0++) {
						for (T a1 = -LIMIT; a1 <= LIMIT; a1++) {
							for (T a2 = -LIMIT; a2 <= LIMIT; a2++) {
								T a0_fixed = fix(a0, m0);
								T a1_fixed = fix(a1, m1);
								T a2_fixed = fix(a2, m2);
								auto res =
									crt<T>({{a0, m0}, {a1, m1}, {a2, m2}});
								auto expected =
									table[a0_fixed][a1_fixed][a2_fixed];
								if (res.has_value()) {
									EXPECT_EQ(res.value().first,
											  expected.value());
									EXPECT_EQ(res.value().second, l);
								} else {
									EXPECT_FALSE(expected.has_value());
								}
							}
						}
					}
				}
			}
		}
	}
}

TEST(TestExtgcd, TestCountSols) {
	EXPECT_EQ(count_sols(1, 1, 3, 0, 4, 0, 4), 4);
}

}  // namespace testing
