#include "contest/base.hpp"

// g(p, k) := f(p^k)
template <class T, class G, class Op>
Vec<T> multiplicative_eval(int n, G g, Op op) {
    auto info = Vec<pair<int, int>>(n + 1);
    auto f = Vec<T>(n + 1);
    f[1] = 1;
    auto primes = Vec<int>();
    for (int a = 2; a <= n; a++) {
        if (info[a].first == 0) {
            info[a] = {1, 1};
            f[a] = g(a, 1);
            primes.push_back(a);
        }
        for (int p : primes) {
            int b = a * p;
            if (b > n) {
                break;
            }
            if (a % p != 0) {
                info[b] = {1, a};
                f[b] = op(f[a], f[p]);
            } else {
                info[b] = {info[a].first + 1, info[a].second};
                f[b] = op(f[info[b].second], g(p, info[b].first));
                break;
            }
        }
    }
    return f;
}