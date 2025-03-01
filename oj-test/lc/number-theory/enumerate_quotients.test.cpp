// verification-helper: PROBLEM https://judge.yosupo.jp/problem/enumerate_quotients

#include "ad-hoc/floor-ceil-range.hpp"
#include "contest/base.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 N;
    std::cin >> N;

    auto quotients = Vec<i64>();
    floor_range(N, [&](i64 q, i64, i64) -> void { quotients.push_back(q); });

    ssize_t num = ssize(quotients);
    std::cout << num << '\n';
    for (ssize_t i = 0; i < num; i++) {
        std::cout << quotients[i] << " \n"[i + 1 == num];
    }

    return 0;
}