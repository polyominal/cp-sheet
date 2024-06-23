/**
 * Author: Hanfei Chen
 * Description: Palindrome tree.
 * Call \texttt{reset()} to move back to the root
 * Status: Tested with
 * - APIO 2014 A
 * - 2023 Hefei Regional
 */

#pragma once

#include "contest/base.hpp"

// 0, ..., K-1
template <int sigma> struct Eertree {
	struct Node { /// start-hash
		array<int, sigma> ch;
		int fail;
		int l, r; // location of the first ocurrence
		Node(int f_, int l_, int r_) : ch{}, fail(f_), l(l_), r(r_) {}
		int len() const { return r-l; }
	};
	Vec<Node> x;
	Vec<int> buf;
	int cur; /// end-hash
	Eertree(int alloc = 0) {
		if (alloc) {
			x.reserve(alloc+2);
			buf.reserve(alloc);
		}
		x.emplace_back(-1, 1, 0);
		x.emplace_back(0, 0, 0);
		reset();
	}

	void reset() {
		cur = 1;
		buf.clear();
	}

	int append(int a) { /// start-hash
		int i = int(buf.size());
		buf.push_back(a);
		auto works = [&](int v) -> bool {
			int l = i - x[v].len();
			return l > 0 && buf[l-1] == a;
		};
		for (; !works(cur); cur = x[cur].fail) {}
		if (!x[cur].ch[a]) {
			int par = x[cur].fail;
			if (par != -1) {
				for (; !works(par); par = x[par].fail) {}
			}
			int npar = (par == -1 ? 1 : x[par].ch[a]);
			x[cur].ch[a] = int(x.size());
			x.emplace_back(npar, i - x[cur].len() - 1, i + 1);
		}
		cur = x[cur].ch[a];
		return cur;
	} /// end-hash

	int size() const {
		return int(x.size());
	}
	const Node& operator [](int i) const {
		return x[i];
	}
};
