#include <catch2/catch_test_macros.hpp>

#include "graph/two-sat.hpp"

TEST_CASE("2sat: simple", "[two-sat]") {
	{
		TwoSat ts(3);
		ts.either(0, 1);
		ts.either(1, 2);
		ts.either(2, 0);
		REQUIRE(ts.solve() == Vec<bool>(3, true));
	}
}