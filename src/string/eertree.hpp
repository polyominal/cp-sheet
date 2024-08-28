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
struct Eertree {
	struct Node {  /// start-hash
		std::forward_list<u32> ch;
		int par, fail;
		int l, r;  // location of the first ocurrence
		int len() const { return r - l; }
		Node(int par_, int fail_, int l_, int r_)
			: par(par_), fail(fail_), l(l_), r(r_) {}
	};
	Vec<Node> nodes;
	Vec<u8> buf;
	int cur;  /// end-hash
	Eertree(int alloc = 0) {
		if (alloc) {
			nodes.reserve(alloc + 2);
			buf.reserve(alloc);
		}
		// 0: EVEN; 1: ODD
		nodes.emplace_back(0, 1, 0, 0);
		nodes.emplace_back(0, 0, 0, -1);
		reset();
	}

	void reset() {
		cur = 1;
		buf.clear();
	}

	int get_ch(int v, u8 x) const {
		for (u32 cw : nodes[v].ch) {
			u8 c = u8(cw);
			if (c == x) return int(cw >> 8);
		}
		return 0;
	}

	int get_fail(int v) const {
		while (buf.back() != buf.end()[-(nodes[v].len() + 2)]) {
			v = nodes[v].fail;
		}
		return v;
	}

	int append(u8 a) {	/// start-hash
		buf.push_back(a);
		cur = get_fail(cur);
		int nxt = get_ch(cur, a);
		if (!nxt) {
			int nf = get_ch(get_fail(nodes[cur].fail), a);
			nxt = int(nodes.size());
			nodes[cur].ch.push_front(a | (nxt << 8));
			nodes.emplace_back(cur, nf, int(buf.size()) - nodes[cur].len() - 2,
							   int(buf.size()));
		}
		cur = nxt;
		return cur;
	}  /// end-hash

	int size() const { return int(nodes.size()); }
	const Node& operator[](int i) const { return nodes[i]; }
};
