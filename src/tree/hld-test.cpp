#include "tree/hld.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "contest/base.hpp"
#include "util/random.hpp"

namespace testing {

Vec<int> get_random_tree_stupid(int n) {
    static auto rng = Random(20240823);
    auto par = Vec<int>(n);
    par[0] = -1;
    for (int i = 1; i < n; i++) {
        par[i] = rng.uniform<int>(0, i - 1);
    }
    return par;
}

HLD get_hld(const Vec<int>& par, int r = 0) {
    int n = int(size(par));
    auto hld = HLD(n);
    for (int i = 0; i < n; i++) {
        if (par[i] != -1) {
            hld.add_edge(i, par[i]);
        }
    }
    hld.build(r);
    return hld;
}

TEST(TestHLD, CompressTree) {
    auto hld = get_hld({2, 2, -1, 0, 1, 0}, 2);

    EXPECT_THAT(hld.compress({1, 0}).first, UnorderedElementsAre(2, 0, 1));
    EXPECT_THAT(hld.compress({5, 3}).first, UnorderedElementsAre(0, 3, 5));
    EXPECT_THAT(hld.compress({5, 3, 4}).first,
                UnorderedElementsAre(2, 0, 3, 5, 4));
    EXPECT_THAT(hld.compress({5, 0, 2}).first, UnorderedElementsAre(2, 0, 5));
}

TEST(TestHLD, Misc) {
    for (int N : {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
        auto par = get_random_tree_stupid(N);
        Vec<int> depth(N);
        depth[0] = 0;
        for (int i = 1; i < N; i++) {
            depth[i] = depth[par[i]] + 1;
        }

        auto tr = Vec<Vec<int>>(N);
        for (int i = 1; i < N; i++) {
            tr[par[i]].push_back(i);
            tr[i].push_back(par[i]);
        }

        auto hld = get_hld(par);

        auto lca_naive = [&](int a, int b) -> int {
            if (depth[a] < depth[b]) {
                swap(a, b);
            }
            while (depth[a] > depth[b]) {
                a = par[a];
            }
            while (a != b) {
                a = par[a], b = par[b];
            }
            return a;
        };
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                EXPECT_EQ(hld.lca(i, j), lca_naive(i, j));
            }
        }

        auto kth_ancestor_naive = [&](int a, int k) -> Opt<int> {
            if (k > depth[a]) {
                return std::nullopt;
            }
            while (k--) {
                a = par[a];
            }
            return a;
        };
        for (int i = 0; i < N; i++) {
            for (int k = 0; k <= N; k++) {
                EXPECT_EQ(hld.get_ancestor(i, k), kth_ancestor_naive(i, k));
            }
        }

        for (int i = 0; i < N; i++) {
            for (int k = 0; k <= depth[i]; k++) {
                EXPECT_EQ(kth_ancestor_naive(i, k),
                          hld.get_lowest(i, [&](int j) -> bool {
                              return depth[j] <= depth[i] - k;
                          }));
            }
        }

        auto in_subtree_naive = [&](int a, int v) -> bool {
            return lca_naive(a, v) == a;
        };
        for (int a = 0; a < N; a++) {
            for (int v = 0; v < N; v++) {
                EXPECT_EQ(hld.in_subtree(a, v), in_subtree_naive(a, v));
            }
        }

        {
            auto path = Vec<int>();
            auto dfs = [&](auto self, int r, int v, int p = -1) -> void {
                path.push_back(v);

                for (size_t d = 0; d < size(path); d++) {
                    EXPECT_EQ(hld.jump(r, v, int(d)).value(), path[d]);
                }
                for (size_t d = size(path); d < size(path) + 5; d++) {
                    EXPECT_EQ(hld.jump(r, v, int(d)), std::nullopt);
                }

                for (int w : tr[v]) {
                    if (w == p) {
                        continue;
                    }
                    self(self, r, w, v);
                }

                path.pop_back();
            };

            for (int r = 0; r < N; r++) {
                dfs(dfs, r, r);
            }
        }
    }
}

}  // namespace testing