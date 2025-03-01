#pragma once

#include <functional>

namespace std {

template <class F>
struct y_combinator_result {
    F f;
    template <class T>
    explicit y_combinator_result(T&& f_) : f(std::forward<T>(f_)) {}
    template <class... A>
    decltype(auto) operator()(A&&... a) {
        return f(std::ref(*this), std::forward<A>(a)...);
    }
};

template <class F>
decltype(auto) y_combinator(F&& f) {
    return y_combinator_result<std::decay_t<F>>(std::forward<F>(f));
}

}  // namespace std