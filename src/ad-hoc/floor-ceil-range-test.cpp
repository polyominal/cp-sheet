#include "ad-hoc/floor-ceil-range.hpp"
#include <gtest/gtest.h>
#include "util/random.hpp"

TEST(FloorCeilRangeTest, FloorRanges) {
    using T = tuple<i64, i64, i64>;
    auto get_ranges = [&](i64 N) -> Vec<T> {
        Vec<T> res;
        auto f = [&](i64 q, i64 l, i64 r) -> void {
            res.emplace_back(q, l, r);
        };
        floor_range(N, f);
        return res;
    };
    auto get_ranges_slow = [&](i64 N) -> Vec<T> {
        Vec<Vec<i64>> buf(N + 1);
        for (i64 x = 1; x <= N; x++) {
            buf[N / x].push_back(x);
        }
        Vec<T> res;
        for (i64 x = 1; x <= N; x++) {
            if (!buf[x].empty()) {
                i64 lo = buf[x][0];
                i64 hi = buf[x].back();
                res.emplace_back(x, lo, hi + 1);
            }
        }
        return res;
    };
    for (i64 N = 1; N <= 200; N++) {
        EXPECT_EQ(get_ranges(N), get_ranges_slow(N));
    }
}

TEST(FloorCeilRangeTest, CeilRanges) {
    using T = tuple<i64, i64, i64>;
    auto get_ranges = [&](i64 N) -> Vec<T> {
        Vec<T> res;
        auto f = [&](i64 q, i64 l, i64 r) -> void {
            res.emplace_back(q, l, r);
        };
        ceil_range(N, f);
        return res;
    };
    auto get_ranges_slow = [&](i64 N) -> Vec<T> {
        Vec<Vec<i64>> buf(N + 1);
        for (i64 x = 1; x <= N; x++) {
            buf[(N - 1) / x + 1].push_back(x);
        }
        Vec<T> res;
        for (i64 x = 1; x <= N; x++) {
            if (x == 1) {
                res.emplace_back(x, N, std::numeric_limits<i64>::max());
                continue;
            }
            if (!buf[x].empty()) {
                i64 lo = buf[x][0];
                i64 hi = buf[x].back();
                res.emplace_back(x, lo, hi + 1);
            }
        }
        return res;
    };
    for (i64 N = 1; N <= 200; N++) {
        EXPECT_EQ(get_ranges(N), get_ranges_slow(N));
    }
}