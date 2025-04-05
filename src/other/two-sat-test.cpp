#include "other/two-sat.hpp"
#include <gtest/gtest.h>

namespace testing {

bool verify_two_sat_case(int n, Vec<pair<int, int>> clauses) {
    auto ts = TwoSat(n);
    for (const auto& [a, b] : clauses) {
        ts.either(a, b);
    }
    if (auto res = ts.solve(); res.has_value()) {
        const auto& sol = res.value();
        auto translate = [](int i) -> pair<int, bool> {
            if (i >= 0) {
                return {i, true};
            } else {
                return {~i, false};
            }
        };
        for (const auto& [a, b] : clauses) {
            auto [a_var, a_val] = translate(a);
            auto [b_var, b_val] = translate(b);
            EXPECT_GE(a_var, 0);
            EXPECT_LE(a_var, n);
            EXPECT_GE(b_var, 0);
            EXPECT_LE(b_var, n);
            EXPECT_TRUE(bool(sol[a_var]) == a_val || bool(sol[b_var]) == b_val);
        }
        return true;
    } else {
        return false;
    }
}

TEST(TestTwoSat, Example) {
    {
        int n = 5;
        auto clauses = Vec<pair<int, int>>{{0, 1},  {~2, ~0}, {~3, ~2},
                                           {1, ~4}, {4, ~1},  {1, 3}};
        EXPECT_TRUE(verify_two_sat_case(n, clauses));
    }
    {
        int n = 2;
        auto clauses = Vec<pair<int, int>>{{0, 1}, {0, ~1}, {1, ~0}, {~0, ~1}};
        EXPECT_FALSE(verify_two_sat_case(n, clauses));
    }
}

}  // namespace testing