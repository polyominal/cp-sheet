#include <gtest/gtest.h>
#include <string/hashed-string-2d.hpp>
#include <string/hashint.hpp>
#include <util/random.hpp>

namespace testing {

TEST(TestHashedString2D, TestSubmatrix) {
	auto rng = Random(20240921);
	for (int n : {1, 2, 3, 5, 8, 13, 21}) {
		auto mat = Vec<Vec<int>>(n, Vec<int>(n));
		constexpr int LIMIT = 1e9;
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				mat[x][y] = rng.uniform(-LIMIT, +LIMIT);
			}
		}

		// auto hm = Hashed2DManager<HashInt>({rand_base(), rand_base()});
		auto hm =
			Hashed2DManager<HashInt>({rng.uniform<u64>(4e10, 5e10) * 2 + 1,
									  rng.uniform<u64>(4e10, 5e10) * 2 + 1});
		auto hashed_mat = hm.make(mat);

		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				for (int dx = 1; x + dx <= n; dx++) {
					for (int dy = 1; y + dy <= n; dy++) {
						auto sub = Vec<Vec<int>>(dx, Vec<int>(dy));
						for (int z = 0; z < dx; z++) {
							std::copy(begin(mat[x + z]) + y,
									  begin(mat[x + z]) + (y + dy),
									  begin(sub[z]));
						}
						auto mapped_sub = hm.get(sub);
						EXPECT_EQ(mapped_sub,
								  hm.get(hashed_mat, {x, x + dx}, {y, y + dy}));
					}
				}
			}
		}
	}
}

}  // namespace testing