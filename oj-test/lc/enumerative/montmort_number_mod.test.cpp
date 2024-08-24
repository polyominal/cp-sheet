// verification-helper: PROBLEM https://judge.yosupo.jp/problem/montmort_number_mod

#include "algebra/barrett.hpp"
#include "contest/base.hpp"
using namespace std;

Vec<u32> montmort(int n, u32 m) {
	if (n <= 1) {
		return {0};
	}

	auto f = Vec<u32>(n);
	f[0] = 0, f[1] = 1;
	auto br = Barrett(m);
	for (int i = 2; i < n; i++) {
		f[i] = br.reduce(u64(i) * (f[i - 1] + f[i - 2]));
	}

	return f;
}

int main() {
	int n;
	u32 m;
	cin >> n >> m;

	for (u32 x : montmort(n, m)) {
		cout << ' ' << x;
	}

	return 0;
}