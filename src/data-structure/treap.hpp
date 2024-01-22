/**
 * Author: Hanfei Chen
 * Description: Randomized Treap with split/merge support.
 * \texttt{nodes.size()} < \texttt{nodes.capacity()}
 * must be maintained.
 * One strategy to save space is
 * to refactor everything when the size of \texttt{nodes}
 * is approximating its capacity
 * Source: me
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
 * Time: O(\log N) per operation
 */

#pragma once

#include "contest/base.hpp"

template <class M, bool persistent = false> struct TreapManager {
	using S = typename M::S;
	using F = typename M::F;

	TreapManager(M m_, int alloc = 0) : m(m_) {
		if (alloc > 0) {
			nodes.reserve(alloc);
		} else {
			// make sure to understand what you're doing
			assert(!persistent);
		}

		mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
		for (int z = 0; z < 2; z++) {
			states[z] = uint32_t(mt());
		}
	}

	using Tree = int;

	Tree make_empty() { return Tree(null); }

	Tree make_single(S s) { /// start-hash
		int i = int(nodes.size());
		nodes.push_back(Node{null, null, 1, false, false, s, s, m.id()});
		return i;
	} /// end-hash

	Tree make_copy(Tree o) { return _make_copy(o); }

	int size(const Tree t) { return _size(t); }
	int reverse(Tree t) { return _reverse(t); }
	int apply(Tree t, F f) { return _apply(t, f); }
	S prod(const Tree& t) { return _prod(t); }

	Tree split_k(Tree& t, int k) { /// start-hash
		Tree o;
		tie(t, o) = _split_k(t, k);
		return o;
	} /// end-hash

	Tree merge(Tree a, Tree b) { return _merge(a, b); }

	Tree build(const V<S>& a) { /// start-hash
		if (a.empty()) return make_empty();
		return _build(a, 0, int(a.size()));
	} /// end-hash

	V<S> to_array(const Tree& t) { /// start-hash
		V<S> buf;
		buf.reserve(size(t));
		_to_array(t, buf);
		return buf;
	} /// end-hash

private:
	static constexpr int null = -42;
	M m;

	struct Node { /// start-hash
		int li, ri, sz;
		bool rev, app;
		S a, s;
		F f;
	};
	V<Node> nodes;
	Node& node(int i) { return nodes[i]; }
	int _size(int i) { return i == null ? 0 : node(i).sz; } /// end-hash

	int _make_copy(int o) { /// start-hash
		if constexpr (!persistent) return o;

		if (o == null) return null;
		assert(nodes.size() < nodes.capacity());
		int i = int(nodes.size());
		nodes.push_back(node(o));
		return i;
	} /// end-hash

	int _build(const V<S>& a, int l, int r) { /// start-hash
		if (r - l == 1) {
			return make_single(a[l]);
		}
		int md = (l + r) / 2;
		return _merge(_build(a, l, md), _build(a, md, r));
	} /// end-hash

	void _update(int i) { /// start-hash
		auto& n = node(i);
		n.s = m.op(_prod(n.li), m.op(n.a, _prod(n.ri)));
		n.sz = size(n.li) + size(n.ri) + 1;
	} /// end-hash

	int _reverse(int i) { /// start-hash
		if (i == null) return i;
		i = _make_copy(i);
		auto& n = node(i);
		n.rev = !n.rev;
		swap(n.li, n.ri);
		return i;
	} /// end-hash

	S _prod(int i) { return i == null ? m.e() : node(i).s; }

	int _apply(int i, F f) { /// start-hash
		if (i == null) return i;
		i = _make_copy(i);
		auto& n = node(i);
		n.s = m.mapping_sz(f, n.s, n.sz);
		n.a = m.mapping_sz(f, n.a, 1);
		n.f = m.composition(f, n.f);
		n.app = true;
		return i;
	} /// end-hash
	
	int downdate(int i) { /// start-hash
		assert(i != null);
		i = _make_copy(i);
		auto& n = node(i);
		if (n.rev) {
			n.li = _reverse(n.li);
			n.ri = _reverse(n.ri);
			n.rev = false;
		}
		if (n.app) {
			n.li = _apply(n.li, n.f);
			n.ri = _apply(n.ri, n.f);
			n.f = m.id();
			n.app = false;
		}
		return i;
	} /// end-hash


	template <class F> pair<int, int> _split(int i, F go_left) { /// start-hash
		if (i == null) return {null, null};
		i = downdate(i);
		auto& n = node(i);
		int li = n.li, ri = n.ri;
		int x, y;
		if (go_left(li, ri)) {
			y = i;
			tie(x, n.li) = _split(n.li, go_left);
		} else {
			x = i;
			tie(n.ri, y) = _split(n.ri, go_left);
		}
		_update(i);
		return {x, y};
	} /// end-hash

	pair<int, int> _split_k(int i, int k) { /// start-hash
		return _split(i, [&](int li, int) -> bool {
			int lsz = size(li);
			if (k <= lsz) {
				return true;
			} else {
				k -= lsz + 1;
				return false;
			}
		});
	} /// end-hash

	// Use std::mt19937_64 if performance is not an issue
	// https://prng.di.unimi.it/xoroshiro64star.c
	inline uint32_t rotl(const uint32_t x, int k) { /// start-hash
		return (x << k) | (x >> (32 - k));
	}
	uint32_t states[2];
	uint32_t rng() {
		const uint32_t s0 = states[0];
		uint32_t s1 = states[1];
		const uint32_t res = s0 * 0x9E3779BB;
		s1 ^= s0;
		states[0] = rotl(s0, 26) ^ s1 ^ (s1 << 9);
		states[1] = rotl(s1, 13);
		return res;
	} /// end-hash

	int _merge(int a, int b) { /// start-hash
		if (a == null) return b;
		if (b == null) return a;
		int r;
		uint32_t sa = size(a), sb = size(b);
		if (rng() % (sa + sb) < sa) {
			r = downdate(a);
			node(r).ri = _merge(node(r).ri, b);
		} else {
			r = downdate(b);
			node(r).li = _merge(a, node(r).li);
		}
		_update(r);
		return r;
	} /// end-hash

	void _to_array(int i, V<S>& buf) { /// start-hash
		if (i == null) return;
		downdate(i);
		auto& n = node(i);
		_to_array(n.li, buf);
		buf.push_back(n.a);
		_to_array(n.ri, buf);
	} /// end-hash
};
