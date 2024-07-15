#include <catch2/catch_test_macros.hpp>

#include "ad-hoc/tree-dp.hpp"
#include "algebra/modint.hpp"
#include "util/random.hpp"

TEST_CASE("Tree DP example", "[tree-dp]") {
    auto rng = Random(20240715);
    for (int N : {1, 2, 3, 5, 8, 13, 21, 34}) {
        using Z = ModInt<998244353>;
        struct E {
            int dest;
            int idx;

            operator int() const {
                return dest;
            }
        };
        struct Manager {
            const Vec<Z>& A, B, C;

            struct Result {
                Z top;
                Z s;
                Z c;
            };
            using S = Result;

            S make(int v) {
                return S{A[v], A[v], 1};
            }
            S op(const S& a, const S& b) {
                assert(a.top == b.top);
                return S{a.top, a.s + b.s - a.top, a.c + b.c - 1};
            }
            S up(const S& a, const E& e) {
                return S{A[e.dest], A[e.dest] + a.s * B[e.idx] + a.c * C[e.idx], a.c + 1};
            }
        };

        auto A = Vec<Z>(N);
        for (auto& a : A) a = rng.uniform<u32>(0, Z::get_mod()-1);
        auto B = Vec<Z>(N-1);
        for (auto& b : B) b = rng.uniform<u32>(0, Z::get_mod()-1);
        auto C = Vec<Z>(N-1);
        for (auto& c : C) c = rng.uniform<u32>(0, Z::get_mod()-1);

        auto m = Manager{.A=A, .B=B, .C=C};
        auto adj = Vec<Vec<E>>(N);
        for (int i = 1; i < N; i++) {
            int p = rng.uniform<int>(0, i-1);
            adj[p].push_back(E{i, i-1});
            adj[i].push_back(E{p, i-1});
        }

        auto tdp = TreeDP(m, adj);
        for (int root = 0; root < N; root++) {
            REQUIRE(tdp[root].c == Z(N));

            auto dfs = [&](auto self, int v, int p) -> pair<Z, Z> {
                auto res = pair<Z, Z>{A[v], 1};
                for (const auto& e : adj[v]) {
                    if (e != p) {
                        pair<Z, Z> ch_res = self(self, e, v);
                        res.first += ch_res.first * B[e.idx] + ch_res.second * C[e.idx];
                        res.second += ch_res.second;
                    }
                }
                return res;
            };
            auto result_naive = dfs(dfs, root, -1);
            REQUIRE(result_naive.second == Z(N));
            REQUIRE(result_naive.first == tdp[root].s);
        }
    }
}