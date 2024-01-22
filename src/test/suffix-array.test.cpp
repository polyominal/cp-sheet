#include <catch2/catch_test_macros.hpp>

#include "contest/base.hpp"
#include "string/suffix-array.hpp"
#include "util/random.hpp"

#include "string/hashint.hpp"

TEST_CASE("Suffix array: simple", "[suffix-array]") {
	auto rng = Random(20240119);
	{
		auto sa = SuffixArray::construct(string("abcbcba"));
		REQUIRE(sa.sa == V<int>{7, 6, 0, 5, 3, 1, 4, 2});
	}
	// permutations of {1, ..., N}
	{
		for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 256, 345}) {
			V<int> perm(N);
			iota(perm.begin(), perm.end(), 1);
			rng.shuffle(perm.begin(), perm.end());

			auto sa = SuffixArray::construct(perm);
			V<int> iperm(N);
			for (int i = 0; i < N; i++) {
				iperm[perm[i]-1] = i;
			}
			REQUIRE(sa.sa[0] == N);
			for (int i = 0; i < N; i++) {
				REQUIRE(iperm[i] == sa.sa[i+1]);
			}
		}
	}
}

template <class S> V<int> get_sa_naive(const S& s) {
	int n = int(s.size());
	using H = HashInt;
	const H base = rand_base();
	V<H> pows(n+1);
	pows[0] = 1;
	for (int i = 1; i <= n; i++) {
		pows[i] = pows[i-1] * base;
	}

	V<H> pref(n+1);
	for (int i = 0; i < n; i++) {
		pref[i+1] = pref[i] * base + H(s[i]);
	}

	V<int> sa(n);
	iota(sa.begin(), sa.end(), 0);
	sort(sa.begin(), sa.end(), [&](int i, int j) -> bool {
		int mi = 0;
		int ma = n - max(i, j) + 1;
		while (ma - mi > 1) {
			int md = (mi + ma) / 2;
			H hi = pref[i + md] - pref[i] * pows[md];
			H hj = pref[j + md] - pref[j] * pows[md];
			if (hi == hj) {
				mi = md;
			} else {
				ma = md;
			}
		}
		return s[i+mi] < s[j+mi];
	});
	sa.insert(sa.begin(), n);
	return sa;
}

TEST_CASE("Suffix array: random", "[suffix-array]") {
	auto rng = Random(20240119);
	{
		for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 256, 345}) {
			string S;
			for (int i = 0; i < N; i++) {
				S.push_back(char('A' + rng.uniform(0, 25)));
			}
			
			auto sa = SuffixArray::construct(S);
			REQUIRE(sa.sa == get_sa_naive(S));
		}
	}
}