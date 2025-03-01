#include "data-structure/queue-aggregation.hpp"
#include <gtest/gtest.h>

namespace testing {

TEST(TestQueueAggregation, Small) {
	auto qa = QueueAggregation([](int a, int b) -> int { return a * b; }, 1);

	EXPECT_TRUE(qa.empty());
	EXPECT_EQ(qa.prod(), 1);
	int cur_prod = 1;

	for (int x = 1; x <= 5; x++) {
		qa.push(x);
		cur_prod *= x;
		EXPECT_FALSE(qa.empty());
		EXPECT_EQ(int(std::size(qa)), x);
		EXPECT_EQ(qa.prod(), cur_prod);
	}

	for (int x = 1; x <= 5; x++) {
		EXPECT_FALSE(qa.empty());
		qa.pop();
		cur_prod /= x;
		EXPECT_EQ(int(std::size(qa)), 5 - x);
		EXPECT_EQ(qa.prod(), cur_prod);
	}

	EXPECT_TRUE(qa.empty());
}

}  // namespace testing