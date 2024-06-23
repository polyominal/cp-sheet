/**
 * Author: Hanfei Chen
 * Description: Persistent array based on persistent segtrees
 * Status: Tested with https://judge.yosupo.jp/problem/persistent_unionfind
 */

#pragma once

#include "contest/base.hpp"

template <class D> struct PersistentArray {
	union N { /// start-hash
		D v;
		array<int, 2> c;
		N(const D& a) : v(a) {}
		N(int a, int b) : c{a, b} {}
	};
	Vec<N> x;
	int s, h;
	// Modify this so that it can reserve memory for x
	PersistentArray() {} /// end-hash

	// All arrays share the same layout (length)
	int build(int n) { /// start-hash
		x.clear();
		s = 1, h = 0;
		while (s < n) {
			s *= 2;
			h++;
		}
		int rt = make_leaf(D());
		for (int l = 0; l < h; l++) {
			rt = make_node(rt, rt);
		}
		return rt;
	} /// end-hash

	int make_leaf(const D& a) { /// start-hash
		x.emplace_back(a);
		return int(x.size())-1;
	}
	int make_node(int a, int b) {
		x.emplace_back(a, b);
		return int(x.size())-1;
	} /// end-hash

	int set(int rt, int i, const D& a) { /// start-hash
		static int buf[40];
		for (int l = 0; l < h; l++) {
			buf[l] = rt;
			if ((i >> (h-1-l)) & 1) {
				rt = x[rt].c[1];
			} else {
				rt = x[rt].c[0];
			}
		}
		int res = make_leaf(a);
		for (int l = h-1; l >= 0; l--) {
			int j = buf[l];
			if ((i >> (h-1-l)) & 1) {
				res = make_node(x[j].c[0], res);
			} else {
				res = make_node(res, x[j].c[1]);
			}
		}
		return res;
	} /// end-hash

	D get(int rt, int i) { /// start-hash
		for (int l = h-1; l >= 0; l--) {
			if (i & (1 << l)) {
				rt = x[rt].c[1];
			} else {
				rt = x[rt].c[0];
			}
		}
		return x[rt].v;
	} /// end-hash
};
