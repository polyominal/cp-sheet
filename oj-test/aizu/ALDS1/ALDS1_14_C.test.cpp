// verification-helper: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_C

#include "string/hashed-string-2d.hpp"
#include "string/hashint.hpp"
#include "util/random.hpp"

int main() {
	using namespace std;

	auto rng = Random(1234);

	auto hm = Hashed2DManager<HashInt>({rng.uniform<u64>(4e10, 5e10) * 2 + 1,
										rng.uniform<u64>(4e10, 5e10) * 2 + 1});
	using Hashed = decltype(hm)::Hashed;
	using Matrix = decltype(hm)::Matrix;

	int H, W;
	cin >> H >> W;
	auto region = Vec<string>(H);
	for (auto& row : region) {
		cin >> row;
	}
	Hashed hashed_region = hm.make(region);

	int R, C;
	cin >> R >> C;
	auto pattern = Vec<string>(R);
	for (auto& row : pattern) {
		cin >> row;
	}
	Matrix hashed_pattern = hm.get(pattern);

	for (int x = 0; x + R <= H; x++) {
		for (int y = 0; y + C <= W; y++) {
			if (hm.get(hashed_region, {x, x + R}, {y, y + C}) ==
				hashed_pattern) {
				cout << x << ' ' << y << '\n';
			}
		}
	}

	return 0;
}