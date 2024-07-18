#include <contest/base.hpp>
#include <util/random.hpp>
#include <string/z-algorithm.hpp>
#include <gtest/gtest.h>

template <class S> Vec<int> z_naive(const S& s) {
	int n = int(size(s));
	auto r = Vec<int>(n+1);
	for (int i = 0; i <= n; i++) {
		int& k = r[i];
		while (i+k < n && s[k] == s[i+k]) k++;
	}
	return r;
}

TEST(ZAlgorithmTest, FibonacciString) {
	auto rng = Random(1145141);
	for (int N : {0, 123, 1234, 2345, 4999}) {
		// Reference: https://github.com/yosupo06/library-checker-problems/blob/master/string/zalgorithm/gen/fib_str.cpp
		string S;
		{
			string a = rng.lowercase_string(rng.uniform(1, 5));
			string b = rng.lowercase_string(rng.uniform(1, 5));
			while (int(size(a) + size(b)) < N) {
				string c = a + b;
				a = b, b = c;
			};
			S = b;
		}

		EXPECT_EQ(z_algo(S), z_naive(S));
	}
}