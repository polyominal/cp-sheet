#include "data-structure/treap.hpp"
#include <gtest/gtest.h>
#include "algebra/modint.hpp"
#include "util/random.hpp"

namespace testing {

constexpr uint32_t MOD = 998244353;

// Value type (sum + count)
struct Value {
    uint32_t sum;

    constexpr static Value e() { return {0}; }

    constexpr Value merge(const Value& other) const {
        return {static_cast<uint32_t>((sum + other.sum) % MOD)};
    }
};

// Affine transformation (ax + b)
struct Affine {
    uint32_t a;
    uint32_t b;

    constexpr static Affine e() { return {1, 0}; }

    constexpr Affine merge(const Affine& other) const {
        return {static_cast<uint32_t>(uint64_t(a) * other.a % MOD),
                static_cast<uint32_t>((uint64_t(b) * other.a + other.b) % MOD)};
    }

    constexpr Value act(const Value& x, const int sz) const {
        return {static_cast<uint32_t>((uint64_t(a) * x.sum + uint64_t(b) * sz) %
                                      MOD)};
    }
};

TEST(TreapTest, DynamicSequenceRangeAffineRangeSum) {
    auto rng = Random(20240107);

    for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
        // TreapManager<Data, false> tm(Data{});
        auto tm = TreapManager<Value, Affine, false>();

        auto A = Vec<Value>(N);
        for (int i = 0; i < N; i++) {
            A[i] = {rng.uniform<uint32_t>(0, MOD - 1)};
        }
        auto tr = tm.build(A);
        EXPECT_EQ(tm.size(tr), N);

        constexpr int Q = 20;
        for (int q = 0; q < Q; q++) {
            {
                int l, r;
                while (true) {
                    l = rng.uniform(0, N);
                    r = rng.uniform(0, N);
                    if (l <= r) {
                        break;
                    }
                }

                auto tr2 = tm.split_k(tr, l);
                auto tr3 = tm.split_k(tr2, r - l);

                // now do something with the interval
                int op = rng.uniform(0, 1);
                if (op == 0) {
                    std::reverse(begin(A) + l, begin(A) + r);
                    tm.reverse(tr2);
                } else if (op == 1) {
                    uint32_t a = rng.uniform<uint32_t>(0, MOD - 1);
                    uint32_t b = rng.uniform<uint32_t>(0, MOD - 1);
                    for (int i = l; i < r; i++) {
                        A[i] = {static_cast<uint32_t>(
                            (uint64_t(a) * A[i].sum + b) % MOD)};
                    }
                    tm.apply(tr2, {a, b});
                } else {
                    assert(false);
                }

                tr = tm.merge(tm.merge(tr, tr2), tr3);
                EXPECT_EQ(tm.size(tr), N);
            }

            for (int l = 0; l <= N; l++) {
                uint32_t tot = 0;
                for (int r = l; r <= N; r++) {
                    auto tr2 = tm.split_k(tr, l);
                    auto tr3 = tm.split_k(tr2, r - l);

                    EXPECT_EQ(tm.prod(tr2).sum, tot);

                    tr = tm.merge(tm.merge(tr, tr2), tr3);
                    if (r < N) {
                        tot = (tot + A[r].sum) % MOD;
                    }
                }
            }
        }
    }
}

}  // namespace testing