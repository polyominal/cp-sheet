#include <catch2/catch_test_macros.hpp>

#include "contest/base.hpp"
#include "graph/eulerian-trail.hpp"

TEST_CASE("Eulerian trail: simple", "[eulerian-trail]") {
	using namespace eulerian_trail;

	{
		int nn = 3;
		int ne = 2;
		VV<E> vs(nn);
		vs[0].emplace_back(1, 0);
		vs[1].emplace_back(2, 1);
		REQUIRE(go(nn, vs, ne, 0) == V<E>{E(0, -1), E(1, 0), E(2, 1)});
		REQUIRE(!go(nn, vs, ne, 1));
		REQUIRE(!go(nn, vs, ne, 2));
	}
}