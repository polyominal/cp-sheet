#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "string/manacher.hpp"

namespace testing {

TEST(ManacherTest, Sample) {
	// Example from https://judge.yosupo.jp/problem/enumerate_palindromes
	auto S = string("mississippi");
	auto man =
		manacher(int(size(S)), [&](int i, int j) { return S[i] == S[j]; });
	EXPECT_THAT(man, ::testing::ElementsAre(0, 1, 0, 1, 0, 1, 4, 1, 0, 7, 0, 1,
											4, 1, 0, 1, 0, 1, 4, 1, 0, 1, 0));
}

}  // namespace testing