#pragma once

#include "contest/base.hpp"

template <class H>
struct HashedManager {
    const H base;
    Vec<H> pows;
    HashedManager(const H& base_) : base(base_), pows({H(1)}) {}

    using Hashed = Vec<H>;
    template <class S>
    Hashed make(const S& s) {
        size_t n = size(s);
        while (size(pows) <= n) {
            pows.push_back(pows.back() * base);
        }
        auto hs = Hashed(n + 1);
        hs[0] = H(0);
        for (size_t i = 0; i < n; i++) {
            hs[i + 1] = hs[i] * base + H(s[i]);
        }
        return hs;
    }

    using Str = pair<H, int>;
    Str get(const Hashed& hs, int l, int r) const {
        return Str(hs[r] - hs[l] * pows[r - l], r - l);
    }
    Str concat(const Str& a, const Str& b) const {
        return Str(a.first * pows[b.second] + b.first, a.second + b.second);
    }
    template <class S>
    Str get(const S& s) {
        auto v = H(0);
        for (auto c : s) {
            v = v * base + H(c);
        }
        return {v, int(size(s))};
    }
};