#pragma once

/**
 * Author: Hanfei Chen
 * Description: Call \texttt{reset()} to move back to the root
 * Status: Tested with
 * - APIO 2014 A
 * - 2023 Hefei Regional
 */

#include "contest/base.hpp"

// 0, ..., K-1
template <int sigma> struct Eertree {
	struct Node {  /// start-hash
		array<int, sigma> ch;
		int par, fail;
		int l, r;  // location of the first ocurrence
		int len() const { return r - l; }
		Node(int par_, int fail_, int l_, int r_)
			: ch{}, par(par_), fail(fail_), l(l_), r(r_) {}
	};
	Vec<Node> nodes;
	Vec<int> buf;
	int cur;  /// end-hash
	Eertree(int alloc = 0) {
		if (alloc) {
			nodes.reserve(alloc + 2);
			buf.reserve(alloc);
		}
		nodes.emplace_back(-1, -1, 1, 0);
		nodes.emplace_back(0, 0, 0, 0);
		reset();
	}

	void reset() {
		cur = 1;
		buf.clear();
	}

	int append(int a) {	 /// start-hash
		int i = int(buf.size());
		buf.push_back(a);
		auto works = [&](int v) {
			int l = i - nodes[v].len();
			return l > 0 && buf[l - 1] == a;
		};
		for (; !works(cur); cur = nodes[cur].fail) {
		}
		if (!nodes[cur].ch[a]) {
			int f = nodes[cur].fail;
			if (f != -1) {
				for (; !works(f); f = nodes[f].fail) {
				}
			}
			int nf = (f == -1 ? 1 : nodes[f].ch[a]);
			nodes[cur].ch[a] = int(nodes.size());
			nodes.emplace_back(cur, nf, i - nodes[cur].len() - 1, i + 1);
		}
		cur = nodes[cur].ch[a];
		return cur;
	}  /// end-hash

	int size() const { return int(nodes.size()); }
	const Node& operator[](int i) const { return nodes[i]; }
};
