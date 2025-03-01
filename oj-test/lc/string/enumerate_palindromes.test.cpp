// verification-helper: PROBLEM https://judge.yosupo.jp/problem/enumerate_palindromes

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "string/manacher.hpp"

int main() {
    using fast_input::Scanner;
    auto sc = Scanner(stdin);

    auto S = std::string();
    sc >> S;

    auto man =
        manacher(int(size(S)), [&](int i, int j) { return S[i] == S[j]; });
    for (auto i = 1; i < ssize(man) - 1; i++) {
        std::cout << man[i] << " \n"[i + 1 == ssize(man) - 1];
    }

    return 0;
}