// verification-helper: PROBLEM https://judge.yosupo.jp/problem/suffixarray

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

    auto sa = SuffixArray::construct(s);
    for (int i = 0; i < n; i++) {
        cout << sa.sa[i] << " \n"[i + 1 == n];
    }

    return 0;
}