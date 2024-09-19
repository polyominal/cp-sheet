// verification-helper: PROBLEM https://judge.yosupo.jp/problem/sum_of_totient_function

#include "algebra/modint.hpp"
#include "contest/base.hpp"
#include "number-theory/eratosthenes.hpp"
#include "number-theory/multiplicative-sum.hpp"

int main() {
	using namespace std;

	i64 N;
	cin >> N;
	auto ps = prime_enumerate(1234567);

	constexpr u32 MOD = 998244353;
	using Z = ModInt<MOD>;
	using multiplicative_sum::get_totient_sum;
	auto res = get_totient_sum<Z>(N, ps);
	cout << res.v << '\n';

	return 0;
}