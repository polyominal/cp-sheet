#include <bits/stdc++.h>
using namespace std;

template <class T> using V = vector<T>;
template <class T> using VV = Vec<Vec<T>>;

using ll = int64_t;

template <class F> struct YCR { /// start-hash
	F f;
	template <class T> explicit YCR(T&& f_) : f(forward<T>(f_)) {}

	template <class... A> decltype(auto) operator()(A&&... as) {
		return f(ref(*this), forward<A>(as)...);
	}
};
template <class F> decltype(auto) YC(F&& f) {
	return YCR<decay_t<F>>(forward<F>(f));
} /// end-hash

int main() {}
