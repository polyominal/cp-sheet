#include <catch2/catch_test_macros.hpp>

#include "string/hashint.hpp"
#include "util/random.hpp"

TEST_CASE("Hashint: bit strings", "[hashint]") {
	auto rng = Random(20240107);

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
		string S;
		for (int i = 0; i < N; i++) {
			S += char('0' + rng.uniform(0, 1));
		}

		V<HashInt> pref(N+1);
		V<HashInt> pows(N+1);
		pows[0] = 1;
		const HashInt base = rand_base();
		for (int i = 0; i < N; i++) {
			pref[i+1] = pref[i] * base + HashInt(S[i]);
			pows[i+1] = pows[i] * base;
		}

		auto query = [&](int l, int r) -> HashInt {
			assert(0 <= l && l <= r && r <= N);
			return pref[r] - pref[l] * pows[r-l];
		};

		for (int l = 0; l <= N; l++) {
			for (int r = l; r <= N; r++) {
				for (int l2 = 0; l2 <= N; l2++) {
					for (int r2 = l2; r2 <= N; r2++) {
						REQUIRE((query(l, r) == query(l2, r2)) == 
								(S.substr(l, r-l) == S.substr(l2, r2-l2)));
					}
				}
			}
		}
	}
}