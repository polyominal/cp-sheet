#include "number-theory/eratosthenes.hpp"
#include <gtest/gtest.h>
#include "util/random.hpp"

namespace testing {

TEST(EratosthenesSieveTest, EnumeratingPrimes) {
    constexpr int MAXN = 1e5;
    auto not_prime = Vec<bool>(MAXN);
    for (int a = 2; a * a < MAXN; a++) {
        if (not_prime[a]) {
            continue;
        }
        for (int b = a * a; b < MAXN; b += a) {
            not_prime[b] = true;
        }
    }
    auto primes = Vec<int>();
    for (int a = 2; a < MAXN; a++) {
        if (!not_prime[a]) {
            primes.push_back(a);
        }
    }

    auto verify_given_N = [&](int N) -> void {
        auto pref = Vec<int>();
        for (int p : primes) {
            if (p <= N) {
                pref.push_back(p);
            } else {
                break;
            }
        }
        EXPECT_EQ(pref, prime_enumerate(N));
    };

    auto rng = Random(20240111);
    for (int z = 0; z < 5; z++) {
        int N = rng.uniform(1, MAXN - 1);
        verify_given_N(N);
    }
    // use prime bounds
    for (int z = 0; z < 5; z++) {
        int prime_idx = rng.uniform(0, int(size(primes)) - 1);
        int N = primes[prime_idx];
        verify_given_N(N);
    }
}

}  // namespace testing