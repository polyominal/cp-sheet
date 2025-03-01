// verification-helper: PROBLEM https://judge.yosupo.jp/problem/sum_of_multiplicative_function

#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "number-theory/eratosthenes.hpp"
#include "number-theory/multiplicative-sum.hpp"

int main() {
    using namespace std;

    using multiplicative_sum::CountingPrime;
    using multiplicative_sum::isqrt;
    using Z = ModInt<469762049>;

    int T;
    cin >> T;
    auto primes = prime_enumerate(500000);
    while (T--) {
        i64 N;
        Z a, b;
        cin >> N >> a.v >> b.v;
        auto cp = CountingPrime<Z, 2>(N, primes, [&](int k, i64 l) -> Z {
            if (k == 0) {
                return Z(l);
            } else if (k == 1) {
                if (l % 2 == 0) {
                    return Z(l / 2) * Z(l + 1);
                } else {
                    return Z(l) * Z((l + 1) / 2);
                }
            } else {
                assert(false);
            }
        });
        auto res = cp.multiplicative_sum(
            {a, b}, [&](i64, int p, int c) -> Z { return a * c + b * p; });
        cout << res.v << '\n';
    }

    return 0;
}