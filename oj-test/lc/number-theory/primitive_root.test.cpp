// verification-helper: PROBLEM https://judge.yosupo.jp/problem/primitive_root

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "number-theory/factor.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    using fast_input::Scanner;
    auto sc = Scanner();

    int Q;
    sc >> Q;

    using factor::primitive_root;

    while (Q--) {
        u64 p;
        sc >> p;
        std::cout << primitive_root(p) << '\n';
    }

    return 0;
}
