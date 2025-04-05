// verification-helper: PROBLEM https://judge.yosupo.jp/problem/number_of_substrings

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "string/suffix-array.hpp"

int main() {
    using namespace std;
    using fast_input::Scanner;

    auto sc = Scanner();
    string s;
    sc >> s;
    int n = int(size(s));

    auto lcp = SuffixArray::construct(s).lcp;
    i64 num_substr = i64(n) * (n + 1) / 2;
    for (i64 x : lcp) {
        num_substr -= x;
    }

    cout << num_substr << '\n';

    return 0;
}