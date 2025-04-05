#include "algebra/modint.hpp"
#include <gtest/gtest.h>
#include "contest/base.hpp"
#include "util/random.hpp"

TEST(TestModInt, MultiplicationAndInversion) {
    auto rng = Random(114514);

    constexpr u32 mod = 998244353;
    using Z = ModInt<mod>;

    for (int z = 0; z < 200; z++) {
        Z a = rng.uniform<u32>(1, mod - 1);
        Z ia = Z(1) / a;
        Z ia2 = inv(a);
        EXPECT_EQ(ia, ia2);
        EXPECT_EQ(a * ia, a * ia2);
        EXPECT_EQ(a * ia, Z(1));
        EXPECT_EQ((a * ia2).v, 1);
    }
}

TEST(TestModInt, TestConstructor) {
    constexpr u32 mod = 998244353;
    using Z = ModInt<mod>;
    EXPECT_EQ(Z(-1), -Z(1));
}