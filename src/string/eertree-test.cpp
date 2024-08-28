#include "string/eertree.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace testing {

TEST(TestEertree, Example) {
	{
		auto et = Eertree<26>();
		auto s = string("abaccaba");
		auto lens = Vec<int>();
		for (char x : s) {
			int v = int(x - 'a');
			lens.push_back(et[et.append(v)].len());
		}
		EXPECT_THAT(lens, ElementsAre(1, 1, 3, 1, 2, 4, 6, 8));
	}
}

}  // namespace testing