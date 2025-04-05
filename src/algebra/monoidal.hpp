#pragma once

#include <concepts>

template <typename T>
concept Monoid = requires(const T& a, const T& b) {
    { T::e() } -> std::same_as<T>;
    { a.merge(b) } -> std::same_as<T>;
    requires std::movable<T>;
    requires std::copyable<T>;
};

template <typename E, typename T>
concept Effect = requires(const E& e, const T& x) {
    { e.act(x) } -> std::same_as<T>;
    requires Monoid<E>;
};