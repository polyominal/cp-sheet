#pragma once

#include "algebra/monoidal.hpp"

template <typename E, typename T>
concept EffectWithSize = requires(const E& e, const T& x, int sz) {
    { e.act(x, sz) } -> std::same_as<T>;
    requires Monoid<E>;
};