#pragma once

#include <span>
#include "algebra/monoidal.hpp"
#include "contest/base.hpp"

template <Monoid T, typename E>
    requires Monoid<T> && Effect<E, T>
struct Node {
    T val;
    E lazy;
    size_t left;
    size_t right;

    Node(T&& val_, E&& lazy_, size_t l_, size_t r_)
        : val(std::move(val_)), lazy(std::move(lazy_)), left(l_), right(r_) {}
};

template <typename T, typename E>
class PersistentLazySegmentTree {
    std::vector<Node<T, E>> pool;
    static constexpr size_t NONE = std::numeric_limits<size_t>::max();

  public:
    PersistentLazySegmentTree(size_t capacity = 0) { pool.reserve(capacity); }

    size_t build(std::span<const T> data) {
        if (data.size() == 1) {
            return create_node(std::move(T(data[0])), std::move(E::e()), NONE,
                               NONE);
        }
        size_t m = data.size() / 2;
        size_t left = build(data.subspan(0, m));
        size_t right = build(data.subspan(m));
        return merge(left, right);
    }

    size_t apply(size_t root, size_t l, size_t r, const E& f, size_t n) {
        return apply_impl(root, 0, n, l, r, E::e(), f);
    }

    T prod(size_t root, size_t l, size_t r, size_t n) const {
        return prod_impl(root, 0, n, l, r, E::e());
    }

    size_t copy(size_t src_root,
                size_t mutator_root,
                size_t l,
                size_t r,
                size_t n) {
        return copy_impl(src_root, mutator_root, 0, n, l, r, E::e(), E::e());
    }

  private:
    size_t create_node(T&& val, E&& lazy, size_t left, size_t right) {
        pool.emplace_back(std::move(val), std::move(lazy), left, right);
        return pool.size() - 1;
    }

    size_t apply_all(size_t node_idx, const E& laz) {
        const auto& node = pool[node_idx];
        T new_val = laz.eval(node.val);
        E new_lazy = node.lazy.merge(laz);
        return create_node(std::move(new_val), std::move(new_lazy), node.left,
                           node.right);
    }

    size_t merge(size_t left, size_t right) {
        return create_node(std::move(pool[left].val.merge(pool[right].val)),
                           std::move(E::e()), left, right);
    }

    size_t apply_impl(size_t idx,
                      size_t s,
                      size_t e,
                      size_t l,
                      size_t r,
                      const E& laz,
                      const E& f) {
        if (l <= s && e <= r) {
            return apply_all(idx, laz.merge(f));
        }
        if (r <= s || e <= l) {
            return apply_all(idx, laz);
        }

        size_t m = (s + e) / 2;
        const auto& node = pool[idx];
        E new_laz = node.lazy.merge(laz);
        return merge(apply_impl(node.left, s, m, l, r, new_laz, f),
                     apply_impl(node.right, m, e, l, r, new_laz, f));
    }

    T prod_impl(size_t idx,
                size_t s,
                size_t e,
                size_t l,
                size_t r,
                const E& laz) const {
        const auto& node = pool[idx];
        if (l <= s && e <= r) {
            return laz.eval(node.val);
        }

        size_t m = (s + e) / 2;
        E new_laz = node.lazy.merge(laz);

        if (r <= m) {
            return prod_impl(node.left, s, m, l, r, new_laz);
        } else if (m <= l) {
            return prod_impl(node.right, m, e, l, r, new_laz);
        } else {
            return prod_impl(node.left, s, m, l, r, new_laz)
                .merge(prod_impl(node.right, m, e, l, r, new_laz));
        }
    }

    size_t copy_impl(size_t src_idx,
                     size_t mutator_idx,
                     size_t s,
                     size_t e,
                     size_t l,
                     size_t r,
                     const E& src_laz,
                     const E& mutator_laz) {
        if (l <= s && e <= r) {
            return apply_all(mutator_idx, mutator_laz);
        }
        if (r <= s || e <= l) {
            return apply_all(src_idx, src_laz);
        }

        const auto& src_node = pool[src_idx];
        const auto& mutator_node = pool[mutator_idx];
        E new_src_laz = src_node.lazy.merge(src_laz);
        E new_mutator_laz = mutator_node.lazy.merge(mutator_laz);

        size_t m = (s + e) / 2;
        size_t left = copy_impl(src_node.left, mutator_node.left, s, m, l, r,
                                new_src_laz, new_mutator_laz);
        size_t right = copy_impl(src_node.right, mutator_node.right, m, e, l, r,
                                 new_src_laz, new_mutator_laz);
        return merge(left, right);
    }
};