#pragma once

/**
 * Author: Hanfei Chen
 * Description: Fast scanner implementation based on \texttt{fread}
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/associative_array (uint64_t)
 */

#include "contest/base.hpp"

namespace fast_input {

struct Scanner {
	FILE* f;
	Scanner(FILE* f_) : f(f_) {}

	void read() {} /// start-hash
	template <class H, class... T> void read(H& h, T&... t) {
		read_single(h);
		read(t...);
	} /// end-hash

	char buf[1 << 16]; /// start-hash
	size_t s = 0, e = 0;
	char get() {
		if (s >= e) {
			buf[0] = 0;
			s = 0;
			e = fread(buf, 1, sizeof(buf), f);
		}
		return buf[s++];
	} /// end-hash

	template <class T> void read_single(T& r) { /// start-hash
		char c;
		while ((c = get()) <= ' ') {}
		bool neg = false;
		if (c == '-') {
			neg = true;
			c = get();
		}
		r = 0;
		do {
			r = 10 * r + (c & 15);
		} while ((c = get()) >= '0');
		if (neg) r = -r;
	} /// end-hash

	void read_single(string& r) { /// start-hash
		char c;
		while ((c = get()) <= ' ') {}
		r = "";
		do {
			r += c;
		} while ((c = get()) > ' ');
	} /// end-hash

	void read_single(double& r) { /// start-hash
		string z;
		read_single(z);
		r = stod(z);
	} /// end-hash
};

} // namespace fast_input
