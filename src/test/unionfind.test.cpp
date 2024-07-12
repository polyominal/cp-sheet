#include <catch2/catch_test_macros.hpp>

#include "data-structure/unionfind.hpp"

TEST_CASE("Union find example", "[unionfind]") {
    auto uf = UnionFind(3);

    REQUIRE(uf.same(1, 1));
    REQUIRE(!uf.same(0, 1));

    REQUIRE(uf.unite(0, 1).has_value());
    REQUIRE(!uf.unite(0, 1).has_value());
    REQUIRE(uf.same(0, 1));

    REQUIRE(uf.unite(1, 2).has_value());
    REQUIRE(!uf.unite(0, 2).has_value());
    REQUIRE(uf.same(0, 2));
    REQUIRE(uf.same(1, 2));
}