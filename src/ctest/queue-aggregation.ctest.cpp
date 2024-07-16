#include <catch2/catch_test_macros.hpp>
#include <queue>

#include "data-structure/queue-aggregation.hpp"
#include "data-structure/static-range.hpp"
#include "util/random.hpp"
#include "algebra/modint.hpp"

TEST_CASE("Queue aggregation: small", "[queue-aggregation]") {
	QueueAggregation qa([&](int a, int b) -> int {
		return a * b;
	}, 1);

	REQUIRE(qa.empty());
	REQUIRE(qa.prod() == 1);
	int cur_prod = 1;

	for (int x = 1; x <= 5; x++) {
		qa.push(x);
		cur_prod *= x;
		REQUIRE(!qa.empty());
		REQUIRE(qa.size() == x);
		REQUIRE(qa.prod() == cur_prod);
	}

	for (int x = 1; x <= 5; x++) {
		REQUIRE(!qa.empty());
		qa.pop();
		cur_prod /= x;
		REQUIRE(qa.size() == 5-x);
		REQUIRE(qa.prod() == cur_prod);
	}

	REQUIRE(qa.empty());
}

TEST_CASE("Queue aggregation: static range product", "[queue-aggregation]") {
	auto rng = Random(20240107);

	constexpr uint32_t mod = 998244353;
	using num = ModInt<mod>;
	using S = num;
	auto op = [](S a, S b) -> S { return a * b; };
	const S e = 1;

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) {
		Vec<S> A(N);
		for (S& a : A) {
			a = rng.uniform<uint32_t>(1, mod-1);
		}
		StaticRange sr(A, op, e);

		auto range_prod_queue = [&](int tgt_l, int tgt_r) -> S {
			REQUIRE(0 <= tgt_l); REQUIRE(tgt_l <= tgt_r); REQUIRE(tgt_r <= N);
			int l = 0, r = 0;
			QueueAggregation qa(op, e);
			while (l < tgt_l || r < tgt_r) {
				REQUIRE(l <= r);
				// move the pointers in some random sense
				if (l == r || l == tgt_l) {
					qa.push(A[r]);
					r++;
				} else if (r == tgt_r) {
					qa.pop();
					l++;
				} else if (rng.uniform_bool()) {
					qa.push(A[r]);
					r++;
				} else {
					qa.pop();
					l++;
				}
			}
			REQUIRE(l == tgt_l); REQUIRE(r == tgt_r);
			return qa.prod();
		};

		for (int l = 0; l <= N; l++) {
			for (int r = l; r <= N; r++) {
				REQUIRE(sr(l, r) == range_prod_queue(l, r));
			}
		}
	}
}