#pragma once

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

#include "contest/base.hpp"

// Work in progress

struct SuffixArray {
	int n;
	Vec<int> sa;
	Vec<int> isa;
	Vec<int> lcp;
	SuffixArray(int n_) : n(n_) {}

	template <class S> static SuffixArray construct(const S& s) {
		int n = int(size(s));
		auto sa = SuffixArray(n);

		sa.build_sa_fast(s);

		sa.build_isa();
		sa.build_lcp(s);

		return sa;
	}

	template <class S> void build_sa_fast(const S& s) {
		auto a = Vec<int>(n);
		int s_min = int(*std::ranges::min_element(s));
		for (int i = 0; i < n; i++) {
			a[i] = int(s[i]) - s_min;
		}
		sa = sais(a);
	}

	static Vec<int> sais(Vec<int> a) {
		int n = int(size(a));
		int m = *std::ranges::max_element(a) + 1;
		auto pos = Vec<int>(m + 1);
		for (auto c : a) pos[c + 1]++;
		std::partial_sum(begin(pos), end(pos), begin(pos));
		auto s = Vec<i8>(n);
		for (int i = n - 2; i >= 0; i--) {
			s[i] = (a[i] != a[i + 1] ? a[i] < a[i + 1] : s[i + 1]);
		}

		auto x = Vec<int>(m);
		auto sa = Vec<int>(n);
		auto induce = [&](const Vec<int>& lms) {
			std::fill(begin(sa), end(sa), -1);
			auto push_L = [&](int i) {
				if (i >= 0 && !s[i]) sa[x[a[i]]++] = i;
			};
			auto push_S = [&](int i) {
				if (i >= 0 && s[i]) sa[--x[a[i]]] = i;
			};
			std::copy(begin(pos) + 1, end(pos), begin(x));
			for (int i = int(size(lms)) - 1; i >= 0; i--) {
				push_S(lms[i]);
			}
			std::copy(begin(pos), end(pos) - 1, begin(x));
			push_L(n - 1);
			for (int i = 0; i < n; i++) {
				push_L(sa[i] - 1);
			}
			std::copy(begin(pos) + 1, end(pos), begin(x));
			for (int i = n - 1; i >= 0; i--) {
				push_S(sa[i] - 1);
			}
		};

		auto ok = [&](int i) { return i == n || (!s[i - 1] && s[i]); };
		auto eq = [&](int i, int j) {
			do {
				if (a[i++] != a[j++]) return false;
			} while (!ok(i) && !ok(j));
			return ok(i) && ok(j);
		};
		auto lms = Vec<int>();
		for (int i = 1; i < n; i++) {
			if (ok(i)) lms.push_back(i);
		}
		induce(lms);

		if (!lms.empty()) {
			int p = -1, w = 0;
			auto mp = Vec<int>(n);
			for (auto v : sa)
				if (v && ok(v)) {
					if (p != -1 && eq(p, v)) w--;
					mp[p = v] = w++;
				}
			auto b = lms;
			for (auto& v : b) v = mp[v];
			b = sais(b);
			for (auto& v : b) v = lms[v];
			induce(b);
		}

		return sa;
	}

	void build_isa() {	/// start-hash
		isa.resize(n);
		for (int i = 0; i < n; i++) isa[sa[i]] = i;
	}  /// end-hash

	template <class S> void build_lcp(const S& s) {
		lcp.resize(n - 1);
		int k = 0;
		for (int i : isa) {
			if (k) k--;
			if (i + 1 < n) {
				int l = sa[i], r = sa[i + 1];
				while (l + k < n && r + k < n && s[l + k] == s[r + k]) k++;
				lcp[i] = k;
			}
		}
	}
};