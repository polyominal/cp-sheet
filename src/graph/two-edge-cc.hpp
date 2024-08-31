#pragma once

#include "graph/dfs-tree.hpp"

template <class G, class F> int two_edge_cc(const G& g, F f) {
	int n = int(g.size());
	auto dfs = DFSTree::make(g);
	auto iord = dfs.get_iord();

	auto low = iord;
	auto seen_par = Vec<u8>(n);
	for (int v = 0; v < n; v++) {
		for (int w : g[v]) {
			if (dfs.par[w] == v && !seen_par[w]) {
				seen_par[w] = 1;
			} else {
				low[w] = min(low[w], iord[v]);
			}
		}
	}
	for (int v : dfs.ord | std::views::reverse) {
		if (int p = dfs.par[v]; p != -1) {
			low[p] = min(low[p], low[v]);
		}
	}

	int n2 = 0;
	auto idx = Vec<int>(n);
	for (int v : dfs.ord) {
		if (low[v] == iord[v]) {
			idx[v] = n2++;
		} else {
			idx[v] = idx[dfs.par[v]];
		}
		f(idx[v], v);
	}

	return n2;
}