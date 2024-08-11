#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2024-07-22
 * Description: All-direction tree DP blackbox
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/tree_path_composite_sum
 * - https://cses.fi/problemset/task/1133
 */

#include "contest/base.hpp"

using std::views::reverse;

template <class S> struct TreeDP {
	template <class RF, class CF> struct Inner {
		Vec<S> low, high;
		Vec<int> edges, par;
		const RF rake;
		const CF compress;
		Inner(const Vec<Vec<int>>& g, auto make, RF rake_, CF compress_)
			: rake(rake_), compress(compress_) {
			int n = int(size(g));
			auto single = Vec<S>(n);
			edges.resize(n - 1);
			for (int v = 0; v < n; v++) {
				single[v] = make(v);
				for (int e : g[v]) edges[e] ^= v;
			}

			auto bfs = Vec<int>{0};
			bfs.reserve(n);
			par.assign(n, -1);
			for (size_t z = 0; z < size(bfs); z++) {
				int v = bfs[z];
				for (int e : g[v]) {
					if (par[v] == e) continue;
					int w = v ^ edges[e];
					par[w] = e;
					bfs.push_back(w);
				}
			}

			low = single;
			auto up = Vec<S>(n);
			auto pref = Vec<S>(n);
			for (int v : bfs | reverse) {
				for (int e : g[v]) {
					if (par[v] == e) continue;
					int w = v ^ edges[e];
					pref[w] = low[v];
					up[w] = compress(low[w], e, v);
					low[v] = rake(low[v], up[w], v);
				}
			}

			high.resize(n);
			auto f = Opt<S>();
			for (int v : bfs) {
				if (v != 0) [[likely]] {
					f = compress(high[v], par[v], v);
				}
				for (int e : g[v] | reverse) {
					if (par[v] == e) continue;
					int w = v ^ edges[e];
					if (f.has_value()) [[likely]] {
						high[w] = rake(pref[w], *f, v);
						f = rake(up[w], *f, v);
					} else {
						high[w] = pref[w];
						f = up[w];
					}
				}
			}
		}

		S get_vertex(int v) const {
			if (v == 0) return low[v];
			return rake(low[v], compress(high[v], par[v], v), v);
		}
	};

	template <class RF, class CF>
	static auto solve(const Vec<Vec<int>>& g, auto make, RF rake, CF compress) {
		return Inner(g, make, rake, compress);
	}
};