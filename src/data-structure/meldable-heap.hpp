#pragma once

#include "contest/base.hpp"

// Comp: (a: T, b: T) -> whether a should be on the top
template <class T, class Comp> struct HeapManager {
	using Heap = int;
	static constexpr Heap null = -42;
	const Comp comp;
	HeapManager(const Comp comp_ = Comp()) : comp(comp_) {}

	Heap make_empty() { return null; }
	Heap make_copy(Heap h) {
		int i = int(size(nodes));
		nodes.push_back(nodes[h]);
		return i;
	}
	Heap make_single(const T& val) {
		int i = int(size(nodes));
		nodes.push_back(Node{{null, null}, val});
		return i;
	}

	Heap meld(Heap a, Heap b) {
		if (a == null) return b;
		if (b == null) return a;
		if (!comp(nodes[a].val, nodes[b].val)) {
			swap(a, b);
		}
		a = make_copy(a);
		nodes[a].ch[1] = meld(nodes[a].ch[1], b);
		swap(nodes[a].ch[0], nodes[a].ch[1]);
		return a;
	}
	Heap insert(Heap h, const T& x) { return meld(h, make_single(x)); }
	Heap pop(Heap h) { return meld(nodes[h].ch[0], nodes[h].ch[1]); }
	Opt<T> top(Heap h) {
		if (h != null) {
			return nodes[h].val;
		} else {
			return std::nullopt;
		}
	}

	struct Node {
		int ch[2];
		T val;
	};
	Vec<Node> nodes;
};