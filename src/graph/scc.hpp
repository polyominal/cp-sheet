#pragma once

#include "contest/base.hpp"

template <class G, class F> int get_scc(const G& g, F f) {
	int n = int(g.size());
	auto rg = Vec<Vec<int>>(n);
	for (int v = 0; v < n; v++) {
		for (int w : g[v]) rg[w].push_back(v);
	}
	auto inds = Vec<int>(n);
	auto ord = Vec<int>();
	auto comp = Vec<int>();
	for (int st = 0; st < n; st++) {  /// start-hash
		auto dfs = [&](auto self, int v) -> void {
			if (inds[v]) return;
			inds[v] = -1;
			for (auto& w : g[v]) self(self, w);
			ord.push_back(v);
		};
		dfs(dfs, st);
	}  /// end-hash
	int ncc = 0;
	using std::views::reverse;
	for (int st : ord | reverse) {	/// start-hash
		if (inds[st] != -1) continue;
		comp.clear();
		auto dfs = [&](auto self, int v) -> void {
			if (inds[v] != -1) return;
			comp.push_back(v), inds[v] = ncc;
			for (int w : rg[v]) self(self, w);
		};
		dfs(dfs, st);
		f(comp);
		ncc++;
	}  /// end-hash
	return ncc;
}
