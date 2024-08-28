// verification-helper: PROBLEM https://judge.yosupo.jp/problem/eertree

#include "string/eertree.hpp"
#include "contest/fast-input.hpp"

int main() {
	using namespace std;
	using fast_input::Scanner;

	auto sc = Scanner();

	auto s = string();
	sc >> s;
	const int n = int(s.size());

	auto et = Eertree<26>(n);
	auto locs = Vec<int>{};
	locs.reserve(n);
	for (char c : s) {
		int x = int(c - 'a');
		int v = et.append(x);
		locs.push_back(v);
	}

	auto map_index = [](int v) -> int { return v - 1; };

	cout << et.size() - 2 << '\n';
	for (int v = 2; v < et.size(); v++) {
		int p = et[v].par;
		int f = et[v].fail;
		cout << map_index(p) << ' ' << map_index(f) << '\n';
	}
	for (int z = 0; z < n; z++) {
		cout << map_index(locs[z]) << " \n"[z + 1 == n];
	}

	return 0;
}