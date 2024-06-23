/**
 * Author: Hanfei Chen
 * Description: NTT; mostly the same with fft.hpp?
 * Status: Tested with https://judge.yosupo.jp/problem/convolution_mod
 */
#pragma once

#include "contest/extra.hpp"

template <class T> void nft(Vec<T>& a, int n) {
	static Vec<int> rev = {0, 1}; /// start-hash
	static Vec<T> rt(2, 1);
	if (int(rt.size()) < n) {
		rev.resize(n);
		for (int i = 0; i < n; i++) {
			rev[i] = (rev[i>>1] | ((i&1)*n)) >> 1;
		}
		rt.reserve(n);
		for (int k = int(rt.size()); k < n; k *= 2) {
			rt.resize(2*k);
			T z = pow(T::get_root(), (T::get_mod()-1) / (2*k));
			for (int i = k/2; i < k; i++) {
				rt[2*i] = rt[i];
				rt[2*i+1] = rt[i] * z;
			}
		}
	} /// end-hash
	int s = __builtin_ctz(int(rev.size()) / n); /// start-hash
	for (int i = 0; i < n; i++) {
		int j = rev[i] >> s;
		if (i < j) swap(a[i], a[j]);
	}
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2*k) {
			auto it1 = a.begin() + i;
			auto it2 = it1 + k;
			for (int j = 0; j < k; j++, ++it1, ++it2) {
				T t = rt[j+k] * *it2;
				*it2 = *it1 - t;
				*it1 += t;
			}
		}
	} /// end-hash
}

template <class T> void inft(Vec<T>& a, int n) { /// start-hash
	T d = inv(T(n));
	for (int i = 0; i < n; i++) a[i] *= d;
	reverse(a.begin()+1, a.begin()+n);
	nft(a, n);
} /// end-hash

template <class T> Vec<T> multiply(Vec<T> a, Vec<T> b) { /// start-hash
	int n = int(a.size()), m = int(b.size());
	if (!n || !m) return {};
	int s = 1 << internal::next_pow2(n + m - 1);
	a.resize(s), nft(a, s);
	b.resize(s), nft(b, s);
	T is = inv(T(s));
	for (int i = 0; i < s; i++) {
		a[i] *= b[i] * is;
	}
	reverse(a.begin() + 1, a.end());
	nft(a, s);
	a.resize(n + m - 1);
	return a;
} /// end-hash