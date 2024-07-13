/**
 * Author: Hanfei Chen
 * Date: 2024-01-12
 * Description: CF932G DP
 * Status: Tested with
 * - https://codeforces.com/contest/932/problem/G (even := true)
 * - https://acm.timus.ru/problem.aspx?space=1&num=2058
 * - https://acm.timus.ru/problem.aspx?space=1&num=2044
 */

#pragma once

#include "contest/base.hpp"
#include "string/eertree.hpp"

// dp[j] := sum_{i s.t. [i, j) is palindromic} {dp[i] * x}
template <class S, int sigma, bool even = false>
Vec<S> palindromic_decomp_dp(const Vec<int>& a,
	auto add, S add_e,
	auto mul_x, S mul_e) {
	int n = int(a.size()); /// start-hash
	Vec<int> locs(n);
	Eertree<sigma> et(n);
	for (int i = 0; i < n; i++) {
		assert(0 <= a[i] && a[i] < sigma);
		locs[i] = et.append(a[i]);
	} /// end-hash

	int nnodes = et.size();
	Vec<int> nxt(nnodes);
	nxt[0] = -1;
	if constexpr (even) {
		assert(n % 2 == 0);
		for (int v = 1; v < nnodes; v++) {
			nxt[v] = (et[v].len() % 2 == 0 ? v : nxt[et[v].fail]);
		}
	} else {
		iota(nxt.begin()+1, nxt.end(), 1);
	}

	Vec<int> diff(nnodes, 1e9); /// start-hash
	Vec<pair<int, int>> top(nnodes);
	for (int v = 2; v < nnodes; v++) {
		int w = nxt[et[v].fail];
		int d = et[v].len() - et[w].len();
		diff[v] = d;
		top[v] = (diff[v] == diff[w] ? top[w] : pair<int, int>(w, 0));
		top[v].second++;
	} /// end-hash

	Vec<S> dp(n+1, add_e), gdp = dp; /// start-hash
	dp[0] = mul_e;
	for (int j = 0; j < n; j++) {
		int v = nxt[locs[j]];
		int i = (j+1) - et[v].len();
		while (v >= 2) {
			int d = diff[v];
			auto [p, s] = top[v];
			if (s == 1) {
				gdp[i] = dp[i];
			} else {
				gdp[i] = add(gdp[i], dp[i + d * (s-1)]);
			}
			dp[j+1] = add(dp[j+1], mul_x(gdp[i]));
			i += d * s;
			v = p;
		}
	} /// end-hash

	return dp;
}