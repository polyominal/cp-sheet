// verification-helper: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite

#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/segtree.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    auto sc = fast_input::Scanner(stdin);

    int N, Q;
    sc >> N >> Q;

    using Z = ModInt<998244353>;
    struct Monoid {
        using S = pair<Z, Z>;

        S e() const { return S{1, 0}; }
        S op(const S& a, const S& b) const {
            return S{a.first * b.first, a.second * b.first + b.second};
        }
    };

    auto segtree = Segtree(
        N,
        [&](int) -> Monoid::S {
            u32 a, b;
            sc >> a >> b;
            return Monoid::S{a, b};
        },
        Monoid());

    for (int q = 0; q < Q; q++) {
        int t;
        sc >> t;
        if (t == 0) {
            int p;
            u32 c, d;
            sc >> p >> c >> d;
            segtree.set(p, Monoid::S{c, d});
        } else if (t == 1) {
            int l, r;
            Z x;
            sc >> l >> r >> x.v;
            auto f = segtree.prod(l, r);
            Z res = f.first * x + f.second;
            std::cout << res.v << '\n';
        } else {
            assert(false);
        }
    }

    return 0;
}