#include "algebra/monoidal.hpp"

// Sum monoid example
template <typename T>
struct Sum {
    using value_type = T;

    T value;

    constexpr Sum merge(const Sum& other) const {
        return {value + other.value};
    }

    constexpr static Sum e() { return T{}; }
};

// Additive effect example
template <Monoid M>
struct AddEffect {
    typename M::value_type delta;

    constexpr AddEffect merge(const AddEffect& other) const {
        return {delta + other.delta};
    }

    constexpr M act(const M& x) const { return {x.value + delta}; }

    constexpr static AddEffect e() { return M{}; }
};

static_assert(Monoid<Sum<int>>);
static_assert(Effect<AddEffect<Sum<int>>, Sum<int>>);

// Affine transformation example
template <typename T>
struct Affine {
    T a;
    T b;

    constexpr Affine merge(const Affine& other) const {
        return {a * other.a, a * other.b + b};
    }

    constexpr T act(T x) const { return a * x + b; }

    constexpr static Affine e() { return {1, 0}; }
};

static_assert(Monoid<Affine<int>>);
static_assert(Effect<Affine<int>, int>);
static_assert(Effect<Affine<long long>, long long>);
static_assert(!Effect<Affine<int>, char>);