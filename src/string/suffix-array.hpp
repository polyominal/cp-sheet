/**
 * Author: Hanfei Chen
 * Date: 2024-01-19
 * Description: Builds the suffix array given a string
 * Source:
 * - https://duck.ac/submission/19987
 * - https://golang.org/src/index/suffixarray/sais.go
 * Time: O(N) building
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/suffixarray
 */

#pragma once

#include "contest/base.hpp"

// Work in progress
// TODO: isa, lcp

struct SuffixArray {
	int n;
	V<int> sa;
	SuffixArray(int n_) : n(n_) {}

	template <class S> static SuffixArray construct(const S& s) {
		int n = int(s.size());
		SuffixArray sa(n);

		sa.build_sa_fast(s);

		return sa;
	}

	template <class S> void build_sa_fast(S s) {
		sa.resize(n+1);
		// kinda weird
		int sigma = 0;
		for (auto v : s) {
			sigma = max(sigma, int(v));
			assert(int(v) > 0);
		}
		++sigma;
		s.push_back(0);
		// what exactly should be these sizes?
		V<int> freq(2 * max(n+1, sigma)), lms(2 * (n+1));
		V<char> type(2 * (n+1));
		sais(n, s.data(), sa.data(), sigma, freq.data(), lms.data(), type.data());
	}

	template <class S> static void sais(int n, S* s, int* sa, int sigma,
										int* freq, int* lms, char* which) {
		int n2 = -1; /// start-hash
		which[n] = 1;
		for (int i = n-1; i >= 0; i--) {
			which[i] = (s[i] == s[i+1] ? which[i+1] : s[i] < s[i+1]);
			if (which[i] == 0 && which[i+1] == 1) {
				which[i+1] = 2;
				lms[++n2] = i+1;
			}
		}
		reverse(lms, lms + (n2+1));
		fill(freq, freq + sigma, 0);
		for (int i = 0; i <= n; i++) ++freq[int(s[i])];
		partial_sum(freq, freq + sigma, freq); /// end-hash

		auto induce = [&](int* v) { /// start-hash
			fill(sa, sa + n+1, 0);
			int* cur = freq + sigma;
			auto pushS = [&](int i) { sa[--cur[int(s[i])]] = i; };
			auto pushL = [&](int i) { sa[cur[int(s[i])]++] = i; };
			copy(freq, freq + sigma, cur);
			for (int i = n2; i >= 0; i--) pushS(v[i]);
			copy(freq, freq + sigma-1, cur + 1);
			for (int i = 0; i <= n; i++) {
				int j = sa[i]-1;
				if (j >= 0 && which[j] == 0) pushL(j);
			}
			copy(freq, freq + sigma, cur);
			for (int i = n; i >= 0; i--) {
				int j = sa[i]-1;
				if (j >= 0 && which[j]) pushS(j);
			}
		}; /// end-hash

		auto eq = [&](int i, int j) { /// start-hash
			if (s[i] == s[j]) {
				while (s[++i] == s[++j]) {
					if (which[i] == 2) return true;
				}
			}
			return false;
		}; /// end-hash

		induce(lms); /// start-hash
		int sigma2 = -1;
		int* s2 = remove_if(sa, sa + n, [&](int i) { return which[i] != 2; });
		for (int i = 0; i <= n2; i++) {
			if (sigma2 <= 0 || !eq(sa[i], sa[i-1])) sigma2++;
			s2[sa[i]>>1] = sigma2;
		}
		for (int i = 0; i <= n2; i++) s2[i] = s2[lms[i]>>1];
		++sigma2;
		if (sigma2 <= n2) {
			sais(n2, s2, sa, sigma2,
				 freq + sigma, lms + (n2+1), which + (n+1));
		} else {
			for (int i = 0; i <= n2; i++) sa[s2[i]] = i;
		}
		auto buf = lms + (n2+1);
		for (int i = 0; i <= n2; i++) buf[i] = lms[sa[i]];
		induce(buf); /// end-hash
	}
};