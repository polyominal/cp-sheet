// verification-helper: PROBLEM https://judge.yosupo.jp/problem/associative_array

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "data-structure/hash-map.hpp"

using std::cout;

int main() {
	std::ios_base::sync_with_stdio(false);

	auto sc = fast_input::Scanner(stdin);

	int Q;
	sc.read(Q);

	using Key = u64;
	using Value = u64;
	auto table = HashMap<Key, Value>();

	for (int q = 0; q < Q; q++) {
		int t;
		Key k;
		sc.read(t, k);
		if (t == 0) {
			Value v;
			sc.read(v);
			table[k] = v;
		} else if (t == 1) {
			auto it = table.find(k);
			if (it != table.end()) {
				cout << it->second << '\n';
			} else {
				cout << 0 << '\n';
			}
		} else {
			assert(false);
		}
	}

	return 0;
}