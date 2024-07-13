/**
 * Author: Hanfei Chen
 * Description: Lazy segtree abstraction
 * Source: ac-library and many others
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/range_affine_range_sum (apply, prod)
 * - https://judge.yosupo.jp/problem/range_affine_point_get (point_get)
 * - https://atcoder.jp/contests/practice2/tasks/practice2_j (max_right)
 * - 2023 Nanjing Regionals Problem M (almost everything?)
 * - https://judge.yosupo.jp/problem/vertex_set_path_composite (set; also justified runtime polymorphism!)
 */

#pragma once

#include "contest/base.hpp"

template <class M> struct LazySegtree {
	using S = M::S;
	using F = M::F;
	M m;
	Vec<S> d;
	Vec<F> lz;
	int n, h, sz;
	LazySegtree(M m_) : m(m_), n(0), h(0), sz(0) {}
	template <class A> LazySegtree(int n_, A a, M m_) : m(m_) {
		build(n_, a);
	}
	template <class A> void build(int n_, A a) { /// start-hash
		n = n_;
		sz = std::bit_ceil<uint32_t>(n);
		h = std::countr_zero<uint32_t>(sz);
		d.resize(2*sz);
		lz.assign(sz, m.id());
		for (int i = 0; i < n; i++) d[sz+i] = a(i);
		for (int i = n; i < sz; i++) d[sz+i] = m.e();
		for (int i = sz-1; i >= 1; i--) update(i);
	} /// end-hash

	void update(int i){ /// start-hash
		d[i] = m.op(d[2*i], d[2*i+1]);
	} /// end-hash

	void apply(int i, F f) { /// start-hash
		d[i] = m.mapping(f, d[i]);
		if (i < sz) lz[i] = m.composition(lz[i], f);
	} /// end-hash

	void downdate(int i) { /// start-hash
		apply(2*i, lz[i]);
		apply(2*i+1, lz[i]);
		lz[i] = m.id();
	} /// end-hash

	void downdate_range(int l, int r) { /// start-hash
		l += sz, r += sz;
		for (int i = h; i >= 1; i--) {
			if (((l >> i) << i) != l) downdate(l >> i);
			if (((r >> i) << i) != r) downdate((r-1) >> i);
		}
	} /// end-hash

	S prod(int l, int r) { /// start-hash
		assert(0 <= l && l <= r && r <= n);
		if (l == r) return m.e();
		downdate_range(l, r);
		S sl = m.e(), sr = m.e();
		for (int a = l+sz, b = r+sz; a < b; a /= 2, b /= 2) {
			if (a & 1) sl = m.op(sl, d[a++]);
			if (b & 1) sr = m.op(d[--b], sr);
		}
		return m.op(sl, sr);
	} /// end-hash

	void apply(int l, int r, F f) { /// start-hash
		assert(0 <= l && l <= r && r <= n);
		if (l == r) return;
		downdate_range(l, r);
		l += sz, r += sz;
		for (int a = l, b = r; a < b; a /= 2, b /= 2) {
			if (a & 1) apply(a++, f);
			if (b & 1) apply(--b, f);
		}
		for (int i = 1; i <= h; i++) {
			if (((l >> i) << i) != l) update(l >> i);
			if (((r >> i) << i) != r) update((r-1) >> i);
		}
	} /// end-hash

	// You can use this to query stuff,
	// which is sometimes more efficient than using prod
	template <class G> void enumerate(int l, int r, G g) { /// start-hash
		assert(0 <= l && l <= r && r <= n);
		if (l == r) return;
		downdate_range(l, r);
		for (int a = l+sz, b = r+sz; a < b; a /= 2, b /= 2) {
			if (a & 1) g(d[a++]);
			if (b & 1) g(d[--b]);
		}
	} /// end-hash

	// Enumerating in some sequential order
	template <bool l_to_r = true, class G>
	void enumerate_in_order(int l, int r, G g) {
		assert(0 <= l && l <= r && r <= n);
		if (l == r) return; /// start-hash
		downdate_range(l, r);
		static Vec<int> ls, rs;
		ls.clear(), rs.clear();
		for (int a = l+sz, b = r+sz; a < b; a /= 2, b /= 2) {
			if (a & 1) ls.push_back(a++);
			if (b & 1) rs.push_back(--b);
		} /// end-hash
		if constexpr (l_to_r) {
			for (int i : ls) g(d[i]);
			for (int z = int(rs.size())-1; z >= 0; z--) g(d[rs[z]]);
		} else {
			for (int i : rs) g(d[i]);
			for (int z = int(ls.size())-1; z >= 0; z--) g(d[ls[z]]);
		}
	}

	const S& all_prod() const { return d[1]; }

	template <class P> pair<int, S> max_right(int l, P p) { /// start-hash
		assert(0 <= l && l <= n);
		if (l == n) return {n, m.e()};
		l += sz;
		for (int i = h; i >= 1; i--) downdate(l >> i);
		S s = m.e();
		assert(p(s));
		do {
			while (l % 2 == 0) l /= 2;
			if (!p(m.op(s, d[l]))) {
				while (l < sz) {
					downdate(l);
					l = 2 * l;
					S t = m.op(s, d[l]);
					if (p(t)) {
						s = t;
						l++;
					}
				}
				return {l-sz, s};
			}
			s = m.op(s, d[l]);
			l++;
		} while ((l & -l) != l);
		return {n, s};
	} /// end-hash

	template <class P> pair<int, S> min_left(int r, P p) { /// start-hash
		assert(0 <= r && r <= n);
		if (r == 0) return {0, m.e()};
		r += sz;
		for (int i = h; i >= 1; i--) downdate((r-1) >> i);
		S s = m.e();
		assert(p(s));
		do {
			r--;
			while (r > 1 && r % 2) r /= 2;
			if (!p(m.op(d[r], s))) {
				while (r < sz) {
					downdate(r);
					r = 2 * r + 1;
					S t = m.op(d[r], s);
					if (p(t)) {
						s = t;
						r--;
					}
				}
				return {r+1-sz, s};
			}
			s = m.op(d[r], s);
		} while ((r & -r) != r);
		return {0, s};
	} /// end-hash

	void set(int p, S s) { /// start-hash
		assert(0 <= p && p < n);
		p += sz;
		for (int i = h; i >= 1; i--) downdate(p >> i);
		d[p] = s;
		for (int i = 1; i <= h; i++) update(p >> i);
	} /// end-hash
};