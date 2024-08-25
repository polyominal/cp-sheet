#pragma once

// Doc: TODO

#include "contest/base.hpp"
#include "data-structure/flatten-vector.hpp"

struct ComplementGraph {
	int n;
	Vec<pair<int, int>> edges;
	ComplementGraph(int n_) : n(n_) {}

	void add_edge(int a, int b) {
		edges.emplace_back(a, b);
		edges.emplace_back(b, a);
	}

	// notifies each connected component
	template <class E> void get_connected(E notify) const {
		auto g = FlattenVector<int>(n, edges);
		auto pending = Vec<int>(n);
		std::iota(begin(pending), end(pending), 0);
		auto bfs = Vec<int>();
		bfs.reserve(n);
		auto skip = Vec<i8>(n);
		while (!pending.empty()) {
			bfs.clear();
			bfs.push_back(pending.back());
			pending.pop_back();
			for (size_t z = 0; z < size(bfs); z++) {
				int v = bfs[z];
				for (int w : g.at(v)) {
					skip[w] = 1;
				}
				for (size_t i = 0; i < size(pending); i++) {
					int w = pending[i];
					if (!skip[w]) {
						bfs.push_back(w);
						pending[i] = pending.back();
						pending.pop_back();
					}
				}
				for (int w : g.at(v)) {
					skip[w] = 0;
				}
			}
			notify(bfs);
		}
	}
};
