// verification-helper: PROBLEM https://judge.yosupo.jp/problem/persistent_range_affine_range_sum

#include "contest/fast-input.hpp"
#include "data-structure/persistent-lazy-segtree.hpp"

constexpr uint32_t MOD = 998244353;

// Value type (sum + count)
struct Value {
    uint32_t sum;
    uint32_t cnt;

    constexpr static Value e() { return {0, 0}; }

    constexpr Value merge(const Value& other) const {
        return {static_cast<uint32_t>((sum + other.sum) % MOD),
                cnt + other.cnt};
    }
};

// Affine transformation (ax + b)
struct Affine {
    uint32_t a;
    uint32_t b;

    constexpr static Affine e() { return {1, 0}; }

    constexpr Affine merge(const Affine& other) const {
        return {static_cast<uint32_t>(uint64_t(a) * other.a % MOD),
                static_cast<uint32_t>((uint64_t(b) * other.a + other.b) % MOD)};
    }

    constexpr Value act(const Value& x) const {
        return {static_cast<uint32_t>(
                    (uint64_t(a) * x.sum + uint64_t(b) * x.cnt) % MOD),
                x.cnt};
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    using fast_input::Scanner;
    auto sc = Scanner(stdin);

    int n, q;
    sc >> n >> q;

    std::vector<Value> initial(n);
    for (int i = 0; i < n; ++i) {
        uint32_t v;
        sc >> v;
        initial[i] = {v, 1};
    }

    PersistentLazySegmentTree<Value, Affine> tree(10'000'000);
    std::vector<size_t> versions = {tree.build(initial)};

    while (q--) {
        int op, k;
        sc >> op >> k;

        if (op == 0) {
            size_t l, r;
            uint32_t a, b;
            sc >> l >> r >> a >> b;
            versions.push_back(tree.apply(versions[k + 1], l, r, {a, b}, n));
        } else if (op == 1) {
            int s;
            size_t l, r;
            sc >> s >> l >> r;
            size_t new_root =
                tree.copy(versions[k + 1], versions[s + 1], l, r, n);
            versions.push_back(new_root);
        } else if (op == 2) {
            size_t l, r;
            sc >> l >> r;
            std::cout << tree.prod(versions[k + 1], l, r, n).sum << '\n';
            versions.push_back(versions.back());  // Dummy version
        } else {
            assert(false);
        }
    }

    return 0;
}
