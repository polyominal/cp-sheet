#include <contest/base.hpp>
#include <string/suffix-array.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(SuffixArrayTest, Sample) {
	{
		auto sa = SuffixArray::construct(string("abcbcba"));
		EXPECT_THAT(sa.sa, testing::ElementsAre(7, 6, 0, 5, 3, 1, 4, 2));
	}
}