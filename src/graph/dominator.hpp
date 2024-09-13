#pragma once

#include "contest/base.hpp"

// idom[i]: intermediate dominator of i
// -1 if i is the rt or not reachable
template <class G> Vec<int> build_idom(int n, const G& g, int rt) {
	auto rg = Vec<Vec<int>>(n);	 /// start-hash
	for (int i = 0; i < n; i++) {
		for (int j : g[i]) rg[j].push_back(i);
	}
	auto sdom = Vec<int>(n);
	auto mi = Vec<int>(n);
	iota(sdom.begin(), sdom.end(), 0);
	iota(mi.begin(), mi.end(), 0);
	/// end-hash

	auto iord = Vec<int>(n, -1);
	auto ord = Vec<int>();
	ord.reserve(n);
	auto par = Vec<int>(n, -1);
	{
		auto dfs = [&](auto self, int v, int p) -> void {  /// start-hash
			if (iord[v] != -1) return;
			iord[v] = int(ord.size());
			ord.push_back(v);
			par[v] = p;
			for (auto& w : g[v]) {
				self(self, w, v);
			}
		};
		dfs(dfs, rt, -1);  /// end-hash
	}

	auto anc = Vec<int>(n, -1);
	auto compress = [&](auto self, int v) -> int {	/// start-hash
		if (anc[v] == -1) return v;
		int a = self(self, anc[v]);
		int& x = mi[v];
		int y = mi[anc[v]];
		if (iord[sdom[x]] > iord[sdom[y]]) {
			x = y;
		}
		return anc[v] = a;
	};	/// end-hash

	auto us = Vec<int>(n);
	auto buc = Vec<Vec<int>>(n);
	using std::views::drop, std::views::reverse;
	for (int w : ord | drop(1) | reverse) {	 /// start-hash
		for (auto& v : rg[w]) {
			if (iord[v] == -1) continue;
			compress(compress, v);
			if (iord[sdom[mi[v]]] < iord[sdom[w]]) {
				sdom[w] = sdom[mi[v]];
			}
		}
		buc[sdom[w]].push_back(w);
		for (int& v : buc[par[w]]) {
			compress(compress, v);
			us[v] = mi[v];
		}
		buc[par[w]].clear();
		anc[w] = par[w];
	}  /// end-hash

	auto idom = Vec<int>(n, -1);
	for (int w : ord | drop(1)) {  /// start-hash
		if (sdom[w] == sdom[us[w]]) {
			idom[w] = sdom[w];
		} else {
			idom[w] = idom[us[w]];
		}
	}  /// end-hash

	return idom;
}