#pragma once

#include "contest/base.hpp"
#include "graph/dfs-tree.hpp"

template <class G, class F> int block_cut_tree(const G& g, F f) {
	int n = int(g.size());
	auto dfs = DFSTree::make(g);
	auto iord = dfs.get_iord();

	auto low = iord;
	for (int v = 0; v < n; v++) {
		for (int w : g[v]) {
			low[v] = min(low[v], iord[w]);
		}
	}
	for (int v : dfs.ord | std::views::reverse) {
		if (int p = dfs.par[v]; p != -1) {
			low[p] = min(low[p], low[v]);
		}
	}

	int nb = 0;
	for (int v : dfs.ord) {
		if (int p = dfs.par[v]; p != -1) {
			if (low[v] < iord[p]) {
				low[v] = low[p];
				f(low[v], v);
			} else {
				low[v] = nb++;
				f(low[v], p);
				f(low[v], v);
			}
		}
	}
	for (int v = 0; v < n; v++) {
		if (g[v].empty()) f(nb++, v);
	}

	return nb;
}