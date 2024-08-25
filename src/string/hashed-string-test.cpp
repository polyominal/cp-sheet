#include <gtest/gtest.h>
#include <string/hashed-string.hpp>
#include <string/hashint.hpp>
#include <util/random.hpp>

namespace testing {

TEST(TestHashedString, StringEquality) {
	// this is somewhat undeterministic but oh well
	const HashInt base = rand_base();
	auto hm = HashedManager(base);

	auto rng = Random(20240825);

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

}  // namespace testing