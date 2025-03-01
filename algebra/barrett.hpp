#pragma once

#include "contest/base.hpp"

struct Barrett {
    static constexpr int k = 96;
    const u32 m;
    const u128 bm;
    Barrett(u32 m_) : m(m_), bm(((u128(1) << k) - 1) / m + 1) {}

    u32 reduce(u64 a) const {
        u64 q = u64((a * bm) >> k);
        return u32(a - q * m);
    }
};