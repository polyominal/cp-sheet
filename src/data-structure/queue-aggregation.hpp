#pragma once

/**
 * Author: Hanfei Chen
 * Description: A queue that supports querying the compositition of all elements
 * Status: Tested with https://judge.yosupo.jp/problem/queue_operate_all_composite
 */

#include "contest/base.hpp"

template <class T, class F> struct QueueAggregation {
	const F f; /// start-hash
	const T e;
	Vec<T> as, bs, ae, be;
	T vs, ve;
	QueueAggregation(F f_, T e_) : f(f_), e(e_), vs(e), ve(e) {} /// end-hash

	void push_s(const T& x) { /// start-hash
		as.push_back(x), bs.push_back(vs = f(x, vs));
	}
	void push_e(const T& x) {
		ae.push_back(x), be.push_back(ve = f(ve, x));
	}
	void reduce() {
		while (!ae.empty()) {
			push_s(ae.back()), ae.pop_back();
		}
		be.clear();
		ve = e;
	} /// end-hash

	bool empty() const { /// start-hash
		return as.empty() && ae.empty();
	}
	int size() const {
		return int(as.size() + ae.size());
	} /// end-hash

	void push(const T& x) { /// start-hash
		if (as.empty()) {
			push_s(x), reduce();
		} else {
			push_e(x);
		}
	}
	void pop() {
		assert(!empty());
		if (as.empty()) reduce();
		as.pop_back(), bs.pop_back();
		vs = (bs.empty() ? e : bs.back());
	}
	T prod() const {
		return f(vs, ve);
	} /// end-hash
};