// verification-helper: PROBLEM https://judge.yosupo.jp/problem/static_range_sum

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/static-range.hpp"

using std::cin, std::cout;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    using fast_input::Scanner;
    auto sc = Scanner(stdin);

    int N, Q;
    sc >> N >> Q;

    using T = u64;

    auto A = Vec<T>(N);
    for (auto& a : A) {
        sc >> a;
    }

    auto sr = StaticRange(A, [](T a, T b) -> T { return a + b; }, T(0));

    for (int q = 0; q < Q; q++) {
        int l, r;
        sc >> l >> r;
        cout << sr.prod(l, r) << '\n';
    }

    return 0;
}