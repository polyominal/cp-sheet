#include "contest/base.hpp"

template <class T> struct CartesianTree {
	int n, root;
	Vec<int> p;
	Vec<array<int, 2>> c;
	CartesianTree(const Vec<T>& a)
		: n(int(size(a))), root(0), p(n, -1), c(n, {-1, -1}) {
		auto stk = Vec<int>{0};
		stk.reserve(n);
		for (int i = 1; i < n; i++) {
			if (a[stk.back()] > a[i]) {
				while (size(stk) >= 2 && a[stk.end()[-2]] > a[i]) {
					stk.pop_back();
				}
				if (size(stk) == 1) {
					root = p[c[i][0] = stk.back()] = i;
				} else {
					p[c[i][0] = stk.back()] = i;
					c[p[i] = stk.end()[-2]][1] = i;
				}
				stk.back() = i;
			} else {
				c[p[i] = stk.back()][1] = i;
				stk.push_back(i);
			}
		}
	}
};