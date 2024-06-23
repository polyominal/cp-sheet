/**
 * Author: Hanfei Chen
 * Date: 2024-01-03
 * Description: Enumerates all triangles $(x,y,z)$ in an undirected graph
 * Time: TODO
 * Status: Tested with https://judge.yosupo.jp/problem/enumerate_triangles
 */

#pragma once

#include "contest/base.hpp"

template <class F> void triangles(int n, const Vec<pair<int, int>>& edges, F f) {
	Vec<int> deg(n); /// start-hash
	for (auto& [a, b] : edges) {
		deg[a]++, deg[b]++;
	}
	Vec<Vec<int>> adj(n);
	for (auto [a, b] : edges) {
		if (tie(deg[a], a) > tie(deg[b], b)) swap(a, b);
		adj[a].push_back(b);
	} /// end-hash

	Vec<int> ind(n); /// start-hash
	int i = 0;
	for (int x = 0; x < n; x++) {
		++i;
		for (int y : adj[x]) ind[y] = i;
		for (int y : adj[x]) {
			for (int z : adj[y]) {
				if (ind[z] == i) f(x, y, z);
			}
		}
	} /// end-hash
}
