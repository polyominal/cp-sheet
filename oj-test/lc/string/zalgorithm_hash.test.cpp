// verification-helper: PROBLEM https://judge.yosupo.jp/problem/zalgorithm

#include "contest/base.hpp"
#include "string/hashed-string.hpp"
#include "string/hashint.hpp"

int main() {
	using namespace std;

	string s;
	cin >> s;
	int n = int(size(s));

	const HashInt base = rand_base();
	auto hm = HashedManager(base);
	auto hs = hm.make(s);

	for (int i = 0; i < n; i++) {
		int mi = 0;
		int ma = n - i + 1;
		while (ma - mi > 1) {
			int md = (mi + ma) / 2;
			if (hm.get(hs, i, i + md) == hm.get(hs, 0, md)) {
				mi = md;
			} else {
				ma = md;
			}
		}
		cout << mi << " \n"[i + 1 == n];
	}

	return 0;
}