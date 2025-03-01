#include "string/hashed-string.hpp"
#include <gtest/gtest.h>
#include "string/hashint.hpp"
#include "util/random.hpp"

namespace testing {

TEST(TestHashedString, StringEquality) {
	auto rng = Random(20241003);

	const auto base = HashInt(rng.uniform<u64>(4e10, 5e10) * 2 + 1);

	auto hm = HashedManager(base);

	for (int m : {1, 2, 3, 5}) {
		auto a = Vec<string>(m);
		for (auto& s : a) {
			int len = rng.uniform(1, 50);
			for (int i = 0; i < len; i++) {
				s += char('a' + rng.uniform(0, 5));
			}
		}

		using Hashed = decltype(hm)::Hashed;
		auto hs = Vec<Hashed>(m);
		for (int z = 0; z < m; z++) {
			hs[z] = hm.make(a[z]);
		}

		for (int x = 0; x < m; x++) {
			for (int y = 0; y < m; y++) {
				int nx = int(size(a[x]));
				int ny = int(size(a[y]));
				for (int xl = 0; xl <= nx; xl++) {
					for (int xr = xl; xr <= nx; xr++) {
						for (int yl = 0; yl <= ny; yl++) {
							for (int yr = yl; yr <= ny; yr++) {
								bool eq = hm.get(hs[x], xl, xr) ==
										  hm.get(hs[y], yl, yr);
								bool eq_expected =
									(xr - xl == yr - yl &&
									 a[x].substr(xl, xr - xl) ==
										 a[y].substr(yl, yr - yl));
								EXPECT_EQ(eq, eq_expected);
							}
						}
					}
				}
			}
		}
	}
}

TEST(TestHashedString, StringConcatenation) {
	auto rng = Random(20241003);

	const auto base = HashInt(rng.uniform<u64>(4e10, 5e10) * 2 + 1);

	auto hm = HashedManager(base);

	for (int n : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
		auto s = string();
		for (int i = 0; i < n; i++) {
			s += char('a' + rng.uniform(0, 25));
		}
		auto hs = hm.make(s);
		EXPECT_EQ(hm.get(hs, 0, n), hm.get(s));

		for (int l = 0; l <= n; l++) {
			for (int m = l; m <= n; m++) {
				for (int r = m; r <= n; r++) {
					auto a = hm.get(hs, l, m);
					auto b = hm.get(hs, m, r);
					auto c = hm.concat(a, b);
					auto d = hm.get(hs, l, r);
					EXPECT_EQ(c, d);
				}
			}
		}
	}
}

}  // namespace testing