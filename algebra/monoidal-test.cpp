#include "algebra/monoidal.hpp"

// Sum monoid example
template <typename T>
struct Sum {
    using value_type = T;

    T value;

    Sum merge(const Sum& other) const { return {value + other.value}; }

    static Sum e() { return T{}; }
};

// Additive effect example
template <Monoid M>
struct AddEffect {
    typename M::value_type delta;

    M eval(const M& x) const { return {x.value + delta}; }

    AddEffect merge(const AddEffect& other) const {
        return {delta + other.delta};
    }

    static AddEffect e() { return M{}; }
};

static_assert(Monoid<Sum<int>>);
static_assert(Effect<AddEffect<Sum<int>>, Sum<int>>);

// Affine transformation example
template <typename T>
struct Affine {
    T a;
    T b;

    Affine merge(const Affine& other) const noexcept {
        return {a * other.a, a * other.b + b};
    }

    static Affine e() noexcept { return {1, 0}; }

    T eval(T x) const noexcept { return a * x + b; }
};

static_assert(Monoid<Affine<int>>);
static_assert(Effect<Affine<int>, int>);
static_assert(Effect<Affine<long long>, long long>);
static_assert(!Effect<Affine<int>, char>);