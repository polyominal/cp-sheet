#include "data-structure/assignment-segtree.hpp"
#include <gtest/gtest.h>
#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "util/random.hpp"

namespace testing {

TEST(AssignmentSegtreeTest, Affine) {
    auto rng = Random(20240130);

    const uint32_t mod = uint32_t(1e9) + 7;
    using num = ModInt<mod>;

    struct Monoid {
        num a;
        num b;

        static Monoid e() { return {1, 0}; }

        Monoid merge(const Monoid& other) const {
            return {a * other.a, a * other.b + b};
        }

        bool operator==(const Monoid& other) const = default;
    };

    for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
        // auto ast = AssignmentSegtree(N, [&A](int i) { return A[i]; });
        auto uniform_affine = [&]() -> Monoid {
            return {num(rng.uniform<uint32_t>(0, mod - 1)),
                    num(rng.uniform<uint32_t>(0, mod - 1))};
        };
        auto A = Vec<Monoid>(N);
        for (int i = 0; i < N; i++) {
            A[i] = uniform_affine();
        }

        auto ast =
            AssignmentSegtree<Monoid>(N, [&](int i) -> Monoid { return A[i]; });

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
                Monoid f = {
                    num(rng.uniform<uint32_t>(0, mod - 1)),
                    num(rng.uniform<uint32_t>(0, mod - 1)),
                };
                for (int i = l; i < r; i++) {
                    A[i] = f;
                }
                ast.assign(l, r, f);
            }

            for (int l = 0; l <= N; l++) {
                Monoid prod = Monoid::e();
                for (int r = l; r <= N; r++) {
                    EXPECT_EQ(prod, ast.prod(l, r));
                    if (r < N) {
                        prod = prod.merge(A[r]);
                    }
                }
            }
        }
    }
}

}  // namespace testing