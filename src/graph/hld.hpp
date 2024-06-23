/**
 * Author: Hanfei Chen
 * Date: 2023-11-09
 * Description: Heavy-light decomposition with derived funcionalities
 * Status: Slightly tested with Library Checker problems.
 * You might want to test it on forests though it seems quite rare.
 * In particular, this is tested with
 * - https://judge.yosupo.jp/problem/vertex_set_path_composite
 */
#pragma once

#include "contest/base.hpp"

struct HLD {
	int n;
	Vec<int> ord, st, en, depth;
	Vec<pair<int, int>> heavy;
	HLD() {}
	HLD(const Vec<int>& par, int rt = -1) { build(par, rt); }

	void build(const Vec<int>& par, int rt = -1) {
		n = int(par.size()); /// start-hash
		ord.resize(n);
		st.resize(n);
		en.resize(n);
		depth.resize(n);
		heavy.resize(n);
		Vec<Vec<int>> ch(n);
		for (int i = 0; i < n; i++) {
			if (par[i] != -1) ch[par[i]].push_back(i);
		} /// end-hash

		int i = 0;
		Vec<int> sub(n);
		auto go = [&](int g) -> void {
			yc([&](auto self, int v, int d = 0) -> void { /// start-hash
				sub[v] = 1;
				depth[v] = d;
				for (int& w : ch[v]) {
					self(w, d+1);
					sub[v] += sub[w];
					if (sub[ch[v][0]] < sub[w]) swap(ch[v][0], w);
				}
			})(g); /// end-hash

			yc([&](auto self, int v, bool r = true) -> void { /// start-hash
				ord[st[v] = i++] = v;
				if (r) {
					heavy[st[v]] = {par[v] == -1 ? -1 : st[par[v]], 1};
				} else {
					heavy[st[v]] = heavy[st[v]-1];
					heavy[st[v]].second++;
				}
				bool cr = false;
				for (int w : ch[v]) {
					self(w, cr);
					cr = true;
				}
				en[v] = i;
			})(g); /// end-hash
		};

		if (rt == -1) {
			// rooted forest
			for (int v = 0; v < n; v++) {
				if (par[v] == -1) go(v);
			}
		} else {
			// rooted at rt
			assert(0 <= rt && rt < n);
			go(rt);
		}

		assert(i == n);
	}

	bool in_subtree(int a, int v) const {
		return st[a] <= st[v] && st[v] < en[a];
	}

	int get_ancestor(int a, int k) const { /// start-hash
		assert(k >= 0);
		a = st[a];
		while (a != -1 && k) {
			if (k >= heavy[a].second) {
				k -= heavy[a].second;
				a = heavy[a].first;
			} else {
				a -= k;
				k = 0;
			}
		}
		if (a == -1) return -1;
		else return ord[a];
	} /// end-hash

	int lca(int a, int b) const { /// start-hash
		a = st[a], b = st[b];
		while (true) {
			if (a > b) swap(a, b);
			if (a > b - heavy[b].second) {
				return ord[a];
			}
			b = heavy[b].first;
			if (b == -1) return -1;
		}
	} /// end-hash

	int jump(int s, int t, int d) const { /// start-hash
		int w = lca(s, t);
		if (d <= depth[s] - depth[w]) {
			return get_ancestor(s, d);
		} else {
			d = (depth[s] + depth[t] - 2 * depth[w]) - d;
			return d >= 0 ? get_ancestor(t, d) : -1;
		}
	} /// end-hash

	Vec<array<int, 2>> extract(int s, int t) { /// start-hash
		static Vec<array<int, 2>> res;
		res.clear();
		s = st[s], t = st[t];
		while (true) {
			if (t > s - heavy[s].second) {
				res.push_back({s, t+1});
				break;
			}
			res.push_back({s, s - heavy[s].second + 1});
			s = heavy[s].first;
		}
		return res;
	} /// end-hash

	template <bool vertex = true, class F> void apply(int s, int t, F f) { /// start-hash
		int a = lca(s, t);
		for (auto&& [x, y] : extract(s, a)) {
			f(x+1, y);
		}
		if constexpr (vertex) {
			f(st[a], st[a]+1);
		}
		auto des = extract(t, a);
		reverse(des.begin(), des.end());
		for (auto&& [x, y] : des) {
			f(y, x+1);
		}
	} /// end-hash

	// NOT TESTED
	template <class F> int get_lowest(int a, F f) const { /// start-hash
		a = st[a];
		while (a != -1) {
			int t = a - heavy[a].second + 1;
			if (!f(ord[t])) {
				a = heavy[a].first;
				continue;
			}
			int mi = t, ma = a+1;
			while (ma - mi > 1) {
				int md = (mi + ma) / 2;
				if (f(ord[md])) mi = md;
				else ma = md;
			}
			return ord[mi];
		}
		return -1;
	} /// end-hash

	Vec<int> inds; /// start-hash
  	pair<Vec<int>, Vec<int>> compress(Vec<int> vs) {
		inds.resize(n, -1);
		auto cmp = [&](int a, int b) -> bool {
			return st[a] < st[b];
		};
		sort(vs.begin(), vs.end(), cmp);
		vs.erase(unique(vs.begin(), vs.end()), vs.end());
		int num = int(vs.size());
		assert(num >= 1);
		for (int z = 1; z < num; z++) {
			vs.push_back(lca(vs[z-1], vs[z]));
		}
		sort(vs.begin(), vs.end(), cmp);
		vs.erase(unique(vs.begin(), vs.end()), vs.end());
		num = int(vs.size());
		for (int z = 0; z < num; z++) inds[vs[z]] = z;
		Vec<int> par(num, -1);
		for (int z = 1; z < num; z++) {
			par[z] = inds[lca(vs[z-1], vs[z])];
		}
		return {vs, par};
  	} /// end-hash
};