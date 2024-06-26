#include <catch2/catch_test_macros.hpp>

#include "string/z-algorithm.hpp"
#include "util/random.hpp"

template <class S> Vec<int> z_naive(const S& s) {
	int n = int(s.size());
	Vec<int> r(n+1);
	for (int i = 0; i <= n; i++) {
		int& k = r[i];
		while (i+k < n && s[k] == s[i+k]) k++;
	}
	return r;
}

TEST_CASE("Z Algorithm: Fibonacci strings", "[z-algorithm]") {
	auto rng = Random(1145141);
	for (int N : {0, 123, 1234, 2345, 4999}) {
		// Reference: https://github.com/yosupo06/library-checker-problems/blob/master/string/zalgorithm/gen/fib_str.cpp
		string S;
		{
			string a = rng.lowercase_string(rng.uniform(1, 5));
			string b = rng.lowercase_string(rng.uniform(1, 5));
			while (int(a.size() + b.size()) < N) {
				string c = a + b;
				a = b, b = c;
			};
			S = b;
		}

		REQUIRE(z_algo(S) == z_naive(S));
	}
}