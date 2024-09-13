// verification-helper: PROBLEM https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum

#include "ad-hoc/offline-query.hpp"

template <class T> using BackupUnit = pair<T*, T>;

int main() {
	using namespace std;

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	auto wgt = Vec<i64>(N);
	for (auto& x : wgt) {
		cin >> x;
	}

	auto prv = map<pair<int, int>, int>();
	auto oq = OfflineQuery<tuple<bool, int, int>, int>();
	for (int q = 0; q < Q; q++) {
		int t;
		cin >> t;

		if (t == 0) {
			int u, v;
			cin >> u >> v;
			if (u > v) {
				swap(u, v);
			}
			prv[{u, v}] = oq.add(make_tuple(false, u, v));
		} else if (t == 1) {
			int u, v;
			cin >> u >> v;
			if (u > v) {
				swap(u, v);
			}
			auto it = prv.find({u, v});
			assert(it != prv.end());
			oq.del(it->second);
		} else if (t == 2) {
			int v, x;
			cin >> v >> x;
			oq.add(make_tuple(true, v, x));
		} else if (t == 3) {
			int v;
			cin >> v;
			oq.ask(v);
		} else {
			assert(false);
		}
	}

	auto backup = Vec<pair<int*, int>>();
	auto backup64 = Vec<pair<i64*, i64>>();
	auto do_backup = [&](int& x) { backup.push_back({&x, x}); };
	auto do_backup64 = [&](i64& x) { backup64.push_back({&x, x}); };
	auto get_snapshots = [&]() -> pair<int, int> {
		return make_pair(int(backup.size()), int(backup64.size()));
	};
	auto do_rollback = [&](pair<int, int> target) {
		auto [snapshot, snapshot64] = target;
		while (int(backup.size()) > snapshot) {
			auto [ptr, val] = backup.back();
			*ptr = val;
			backup.pop_back();
		}
		while (int(backup64.size()) > snapshot64) {
			auto [ptr, val] = backup64.back();
			*ptr = val;
			backup64.pop_back();
		}
	};

	auto uf = Vec<int>(N, -1);
	auto get_root = [&](auto self, int v) -> int {
		return uf[v] < 0 ? v : self(self, uf[v]);
	};
	auto unite = [&](int a, int b) -> Opt<pair<int, int>> {
		a = get_root(get_root, a);
		b = get_root(get_root, b);
		if (a == b) {
			return nullopt;
		}

		if (-uf[a] < -uf[b]) {
			swap(a, b);
		}
		do_backup(uf[a]);
		do_backup(uf[b]);
		uf[a] += uf[b];
		uf[b] = a;
		return pair<int, int>(a, b);
	};
	auto do_unite = [&](int a, int b) -> void {
		if (auto u = unite(a, b); u.has_value()) {
			auto [ra, rb] = u.value();
			do_backup64(wgt[ra]);
			wgt[ra] += wgt[rb];
		}
	};
	auto do_add = [&](int v, int x) -> void {
		v = get_root(get_root, v);
		do_backup64(wgt[v]);
		wgt[v] += x;
	};

	auto snapshots = Vec<pair<int, int>>();
	auto upd = [&](tuple<bool, int, int> q) {
		snapshots.push_back(get_snapshots());
		bool t = get<0>(q);
		if (t) {
			do_add(get<1>(q), get<2>(q));
		} else {
			do_unite(get<1>(q), get<2>(q));
		}
	};
	auto undo = [&]() {
		do_rollback(snapshots.back());
		snapshots.pop_back();
	};
	auto ask = [&](int v) {
		v = get_root(get_root, v);
		cout << wgt[v] << '\n';
	};
	oq.exec(upd, undo, ask);

	assert(snapshots.empty());
	assert(uf == Vec<int>(N, -1));

	return 0;
}