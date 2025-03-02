#include "data-structure/persistent-lazy-segtree.hpp"
#include <gtest/gtest.h>
#include "contest/base.hpp"

namespace testing {

struct Pair {
    int64_t value;
    int size;

    Pair(const int64_t value_, const int size_ = 1)
        : value(value_), size(size_) {}

    Pair merge(const Pair& other) const {
        return Pair(value + other.value, size + other.size);
    }
    static Pair e() { return Pair(0, 0); }
};

struct Affine {
    int64_t a;
    int64_t b;

    Affine(const int64_t& a_, const int64_t& b_) : a(a_), b(b_) {}

    Affine merge(const Affine& other) const noexcept {
        return Affine(a * other.a, b * other.a + other.b);
    }

    static Affine e() noexcept { return Affine(1, 0); }

    Pair eval(Pair x) const noexcept {
        return {a * x.value + b * x.size, x.size};
    }
};

TEST(TestPersistentLazySegmentTree, DegeneratedExample) {
    using T = Pair;
    using E = Affine;

    auto st = PersistentLazySegmentTree<T, E>();

    auto t_0 = st.build(Vec<T>{1, 2, 3, 4, 5});
    EXPECT_EQ(st.prod(t_0, 0, 5, 5).value, 15);

    auto t_1 = st.apply(t_0, 0, 5, E{2, 1}, 5);
    // 2 * 15 + 5 = 35
    auto prod = st.prod(t_1, 0, 5, 5);
    EXPECT_EQ(prod.size, 5);
    EXPECT_EQ(prod.value, 35);

    auto t_2 = st.copy(t_0, t_1, 0, 3, 5);
    // 15 + (1 + 2 + 3) + 3 = 24
    prod = st.prod(t_2, 0, 5, 5);
    EXPECT_EQ(prod.size, 5);
    EXPECT_EQ(prod.value, 24);

    auto t_3 = st.copy(t_2, t_0, 0, 3, 5);
    // Back to 15
    prod = st.prod(t_3, 0, 5, 5);
    EXPECT_EQ(prod.size, 5);
    EXPECT_EQ(prod.value, 15);

    auto t_4 = st.apply(t_1, 0, 2, E{3, 2}, 5);
    // 35 + 2 * (3 + 5) + 2 * 2 = 55
    prod = st.prod(t_4, 0, 5, 5);
    EXPECT_EQ(prod.size, 5);
    EXPECT_EQ(prod.value, 55);
}

}  // namespace testing