#include <gtest/gtest.h>
#include <data-structure/line-container.hpp>

using line_container::LineContainer;

namespace testing {

TEST(TestLineContainer, Example) {
	auto lc = LineContainer();
	lc.add(1, 1);
	lc.add(0, -1);
	EXPECT_EQ(lc.query(-1), 0);
	EXPECT_EQ(lc.query(-2), -1);
}

}  // namespace testing