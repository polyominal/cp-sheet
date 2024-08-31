#pragma once

/**
 * Author: Hanfei Chen
 * Date: 2024-01-03
 * Description: Enumerates all triangles $(x,y,z)$ in an undirected graph
 * Time: TODO
 * Status: Tested with https://judge.yosupo.jp/problem/enumerate_triangles
 */

#include "contest/base.hpp"
#include "data-structure/flatten-vector.hpp"

template <class F> void triangles(int n, Vec<pair<int, int>> edges, F f) {
	auto deg = Vec<int>(n);
	for (auto [a, b] : edges) {
		deg[a]++;
		deg[b]++;
	}
	for (auto& [a, b] : edges) {
		if (tie(deg[a], a) > tie(deg[b], b)) {
			swap(a, b);
		}
	}
	auto adj = FlattenVector<int>(n, edges);

	Vec<int> ind(n);
	int i = 0;
	for (int x = 0; x < n; x++) {
		++i;
		for (int y : adj[x]) ind[y] = i;
		for (int y : adj[x]) {
			for (int z : adj[y]) {
				if (ind[z] == i) {
					f(x, y, z);
				}
			}
		}
	}
}
