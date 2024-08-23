// verification-helper: PROBLEM https://judge.yosupo.jp/problem/cartesian_tree

#include "contest/base.hpp"
#include "tree/cartesian-tree.hpp"

int main() {
	using namespace std;

	int N;
	cin >> N;
	auto A = Vec<int>(N);
	for (int& a : A) cin >> a;

	auto ct = CartesianTree(A);
	auto p = ct.p;
	p[ct.root] = ct.root;
	for (int i = 0; i < N; i++) {
		cout << p[i] << " \n"[i + 1 == N];
	}

	return 0;
}