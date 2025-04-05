#pragma once

#include "contest/base.hpp"

template <class H>
struct Hashed2DManager {
    const array<H, 2> base;
    array<Vec<H>, 2> pows;
    Hashed2DManager(const array<H, 2>& base_)
        : base(base_), pows({{H(1)}, {H(1)}}) {}

    using Hashed = Vec<Vec<H>>;
    template <class S>
    Hashed make(const Vec<S>& s) {
        array<size_t, 2> n = {size(s), size(s[0])};  /// start-hash
        for (int z = 0; z < 2; z++) {
            while (size(pows[z]) <= n[z]) {
                pows[z].push_back(pows[z].back() * base[z]);
            }
        }
        auto hs = Hashed(n[0] + 1, Vec<H>(n[1] + 1));
        hs[0][0] = H(0);
        for (size_t x = 0; x < n[0]; x++) {
            hs[x + 1][0] = H(0);
            for (size_t y = 0; y < n[1]; y++) {
                hs[x + 1][y + 1] = hs[x + 1][y] * base[1] + H(s[x][y]);
            }
        }
        for (size_t y = 0; y < n[1]; y++) {
            hs[0][y + 1] = H(0);
            for (size_t x = 0; x < n[0]; x++) {
                hs[x + 1][y + 1] = hs[x][y + 1] * base[0] + hs[x + 1][y + 1];
            }
        }
        return hs;  /// end-hash
    }

    using Matrix = pair<H, array<int, 2>>;  // {hash, dimensions}
    // x: [x[0], x[1]), y: [y[0], y[1])
    /// start-hash
    Matrix get(const Hashed& hs, array<int, 2> x, array<int, 2> y) const {
        return {
            hs[x[1]][y[1]] - hs[x[0]][y[1]] * pows[0][x[1] - x[0]] -
                hs[x[1]][y[0]] * pows[1][y[1] - y[0]] +
                hs[x[0]][y[0]] * pows[0][x[1] - x[0]] * pows[1][y[1] - y[0]],
            {x[1] - x[0], y[1] - y[0]}};
    }
    /// end-hash

    template <class S>
    Matrix get(const Vec<S>& s) {
        auto v = H(0);  /// start-hash
        for (size_t x = 0; x < size(s); x++) {
            auto t = H(0);
            for (size_t y = 0; y < size(s[0]); y++) {
                t = t * base[1] + H(s[x][y]);
            }
            v = v * base[0] + t;
        }
        return {v, {int(size(s)), int(size(s[0]))}};  /// end-hash
    }
};