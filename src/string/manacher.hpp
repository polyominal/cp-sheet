/**
 * Author: Hanfei Chen
 * Date: 2024-01-03
 * Source: https://github.com/hos-lyric/libra/blob/master/string/palindrome.cpp
 * Description: Returns maximum lengths of
 * ``palindromic'' (whatever that means)
 * substring of S centered at each point
 * Time: O(N)
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/enumerate_palindromes
 * - https://ac.nowcoder.com/acm/contest/57357/G
 */

#pragma once

#include "contest/base.hpp"

/*
 * eq(i, j): whether [i, j] (inclusive) is palindromic,
 * given that [i+1, j-1] is palindromic.
 * Properties:
 *   * res[i] == i (mod 2)
 *   * k + res[i-k] < res[i] => res[i+k] = res[i-k]
 *   * k + res[i-k] >= res[i] => res[i-k] >= res[i] - k
 * [i, j) being palindromic <=> j-i <= res[i+j]
 * In particular, res[2*i+1] = -1 states that [i, i] is not palindromic.
 */
template <class E> Vec<int> manacher(int n, E e) {
	Vec<int> res(2*n+1);
	int i = 0, a = 0, b = 0;
	while (i <= 2*n) {
		while (0 < a && b < n) {
			if (i-2*a >= -1 && !e(a-1, b)) break;
			a--, b++;
		}
		int j = b-a;
		res[i] = j;
		int k = 1;
		while (k < j && k + res[i-k] < j) {
			res[i+k] = res[i-k];
			k++;
		}
		i += k, a += k;
	}
	return res;
}
