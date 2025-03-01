#pragma once

#include "contest/base.hpp"

template <class T>
tuple<T, T, T> extgcd(T a, T b) {
    if (b == 0) {  /// start-hash
        return {1, 0, a};
    }
    auto [x, y, g] = extgcd(b, a % b);
    return {y, x - a / b * y, g};  /// end-hash
}

template <class T, class U>
U fix(T a, U m) {
    a %= m;
    if (a < 0) {
        a += m;
    }
    return U(a);
}

template <class T>
Opt<T> minv(T a, T m) {
    a %= m;  /// start-hash
    auto [x, y, g] = extgcd(a, m);
    if (g == 1) {
        return fix(x, m);
    }
    return std::nullopt;  /// end-hash
}

template <class T>
Opt<pair<T, T>> crt(T a1, T m1, T a2, T m2) {
    auto [x, y, g] = extgcd(m1, m2);  /// start-hash
    a1 = fix(a1, m1);
    a2 = fix(a2, m2);
    if (a1 % g != a2 % g) {
        return std::nullopt;
    }
    x = fix(i128(x) * a2, m2);
    y = fix(i128(y) * a1, m1);
    T lcm = m1 * (m2 / g);
    return pair<T, T>(fix(i128(x) * (m1 / g) + i128(y) * (m2 / g), lcm),
                      lcm);  /// end-hash
}

template <class T>
Opt<pair<T, T>> crt(const Vec<pair<T, T>>& cons) {
    auto res = Opt<pair<T, T>>({0, 1});  /// start-hash
    for (auto [a, m] : cons) {
        if (res = crt(res.value().first, res.value().second, a, m);
            !res.has_value()) {
            break;
        }
    }
    return res;  /// end-hash
}

// Precondition: a and b are non-zero
template <class T>
Opt<tuple<T, T, T>> find_any(T a, T b, T c) {
    assert(a && b);  /// start-hash
    auto [x0, y0, g] = extgcd(abs(a), abs(b));
    if (c % g != 0) {
        return std::nullopt;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) {
        x0 = -x0;
    }
    if (b < 0) {
        y0 = -y0;
    }
    return tuple<T, T, T>(x0, y0, g);  /// end-hash
}

// # of (x, y) s.t. ax + by = c and
// xmin <= x and x <= xmax and ymin <= y and y <= ymax
template <class T>
T count_sols(T a, T b, T c, T xl, T xr, T yl, T yr) {
    if (c < 0) {  /// start-hash
        a = -a, b = -b, c = -c;
    }
    if (a < 0) {
        a = -a, swap(xl, xr), xl = -xl, xr = -xr;
    }
    if (b < 0) {
        b = -b, swap(yl, yr), yl = -yl, yr = -yr;
    }
    auto len = [&](T lo, T hi) { return max<T>(0, hi - lo + 1); };
    auto cont = [&](T v, T lo, T hi) { return lo <= v && v <= hi; };
    if (!a && !b) {
        return c == 0 ? len(xl, xr) * len(yl, yr) : 0;
    }
    if (!a) {
        return c % b == 0 && cont(c / b, yl, yr) ? len(xl, xr) : 0;
    }
    if (!b) {
        return c % a == 0 && cont(c / a, xl, xr) ? len(yl, yr) : 0;
    }
    if (auto sol = find_any(a, b, c); sol.has_value()) {
        auto [x, y, g] = sol.value();
        using D = double;
        auto fdiv = [&](T p, T q) -> T { return T(floor(D(p) / q)); };
        auto cdiv = [&](T p, T q) -> T { return T(ceil(D(p) / q)); };
        a /= g, b /= g, c /= g;
        T lo = max(cdiv(xl - x, b), cdiv(y - yr, a));
        T hi = min(fdiv(xr - x, b), fdiv(y - yl, a));
        return len(lo, hi);
    } else {
        return 0;
    }  /// end-hash
}