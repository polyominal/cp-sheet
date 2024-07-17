#include <gtest/gtest.h>
#include <contest/base.hpp>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);

	int x = std::uniform_int_distribution<int>(2, 2)(mt);
	EXPECT_EQ(x, 2);
}