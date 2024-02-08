/**
 * Author: Hanfei Chen
 * Date: 2024-01-18
 * Description: Eulerian undirected/directed trail algorithm.
 * Returns a list of (vertex, edge)'s in the trail
 * with \texttt{src} at the start,
 * or \texttt{std::nullopt} if there is no trail.
 * Note that choosing the starting vertex
 * can be somewhat ad-hoc :)
 * Time: $O(V+E)$
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/eulerian_trail_directed (trail_directed)
 * - https://judge.yosupo.jp/problem/eulerian_trail_undirected (trail_undirected)
 * - https://uoj.ac/problem/117 (go)
 */

#pragma once

#include "contest/base.hpp"

namespace eulerian_trail {

// (vertex, edge)
// For the returned list,
// edge is the preceding edge of that vertex
using E = pair<int, int>;
template <bool cyc_only = false>
optional<V<E>> go(int nv, const VV<E>& g, int ne, int src = 0) {
	assert(nv == int(g.size()));
	assert(0 <= src && src < nv);

	V<V<E>::const_iterator> its(nv); /// start-hash
	for (int i = 0; i < nv; i++) its[i] = g[i].begin();
	V<int> state(nv);
	if constexpr (!cyc_only) state[src]++;
	V<bool> seen(ne);
	V<E> res, stk = {E(src, -1)}; /// end-hash

	while (!stk.empty()) { /// start-hash
		auto [i, p] = stk.back();
		auto& it = its[i];
		if (it == g[i].end()) {
			res.emplace_back(i, p);
			stk.pop_back();
			continue;
		}
		auto [j, e] = *(it++);
		if (!seen[e]) {
			state[i]--, state[j]++;
			stk.emplace_back(j, e);
			seen[e] = true;
		}
	}
	if (int(res.size()) != ne+1) return {};
	for (int s : state) if (s < 0) return {};
	return V<E>{res.rbegin(), res.rend()}; /// end-hash
}

template <bool cyc_only = false>
optional<V<E>> trail_undirected(int nv, const V<pair<int, int>>& edges) {
	assert(nv > 0);

	VV<E> g(nv);
	int e = 0;
	for (auto [a, b] : edges) {
		g[a].emplace_back(b, e);
		g[b].emplace_back(a, e);
		e++;
	}

	int src = 0; /// start-hash
	for (int i = 0; i < nv; i++) {
		if (!g[i].empty()) src = i;
	}
	for (int i = 0; i < nv; i++) {
		if (g[i].size() % 2 == 1) src = i;
	} /// end-hash
	return go<cyc_only>(nv, g, int(edges.size()), src);
}

template <bool cyc_only = false>
optional<V<E>> trail_directed(int nv, const V<pair<int, int>>& edges) {
	assert(nv > 0);

	VV<E> g(nv);
	V<int> indeg(nv);
	int e = 0;
	for (auto [a, b] : edges) {
		g[a].emplace_back(b, e);
		indeg[b]++;
		e++;
	}

	int src = 0; /// start-hash
	for (int i = 0; i < nv; i++) {
		if (!g[i].empty()) src = i;
	}
	for (int i = 0; i < nv; i++) {
		if (indeg[i] < int(g[i].size())) src = i;
	} /// end-hash
	return go<cyc_only>(nv, g, int(edges.size()), src);
}

} // namespace eulerian_trail