/**
 * Author: Hanfei Chen
 * Date: 2024-01-30
 * Description: Range assignment and range composition
 * on a sequence of monoid
 * Source: https://maspypy.com/library-checker-range-set-range-composite
 * Status: Tested with https://judge.yosupo.jp/problem/range_set_range_composite
 */

#pragma once

#include "contest/base.hpp"
#include "data-structure/fast-set.hpp"
#include "data-structure/segtree.hpp"

template <class M> struct AssignmentSegtree {
	using S = typename M::S;
	M m;
	int n;
	Segtree<M> st;
	FastSet cut;
	V<S> dat;

	AssignmentSegtree(M m_) : m(m_), n(0), st(m) {}
	AssignmentSegtree(int n_, M m_) : m(m_), st(m) {
		build(n_);
	}
	AssignmentSegtree(const V<S>& a, M m_) : m(m_), n(int(a.size())), st(m) {
		build(a);
	}
	template <class A> AssignmentSegtree(int n_, A a, M m_) : m(m_), n(n_), st(m) {
		build(n_, a);
	}

	void build(int n_) {
		n = n_;
		st.build(n);
		init();
	}
	void build(const V<S>& a) {
		n = int(a.size());
		st.build(a);
		init();
	}
	template <class A> void build(int n_, A a) {
		n = n_;
		st.build(n, a);
		init();
	}

	void init() {
		cut = FastSet(n);
		for (int p = 0; p < n; p++) cut.set(p);
		dat = st.to_array();
	}

	S pow(S s, int b) {
		S r = m.e();
		while (b) {
			if (b & 1) r = m.op(r, s);
			s = m.op(s, s);
			b >>= 1;
		}
		return r;
	}

	S prod(int l, int r) {
		if (l == r) return m.e();
		int a = cut.prev(l);
		int b = cut.next(l);
		int c = cut.prev(r);
		if (a == c) {
			return pow(dat[a], r-l);
		}
		S u = pow(dat[a], b-l);
		S v = st.prod(b, c);
		S w = pow(dat[c], r-c);
		return m.op(u, m.op(v, w));
	}

	void assign(int l, int r, S s) {
		if (l == r) return;
		int a = cut.prev(l);
		int b = cut.next(r);
		if (a < l) {
			st.set(a, pow(dat[a], l-a));
		}
		if (r < b) {
			S t = dat[cut.prev(r)];
			dat[r] = t;
			cut.set(r);
			st.set(r, pow(t, b-r));
		}
		cut.enumerate(l+1, r, [&](int i) -> void {
			st.set(i, m.e());
			cut.reset(i);
		});
		dat[l] = s;
		cut.set(l);
		st.set(l, pow(s, r-l));
	}
};
