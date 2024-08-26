// verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_A

#include "geometry/ccw.hpp"

using geometry::ccw;
using geometry::Point;

int main() {
	using namespace std;

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int Q;
	cin >> Q;
	using P = Point<i64>;
	while (Q--) {
		P a, b, c, d;
		cin >> a >> b >> c >> d;
		P u = b - a;
		P v = d - c;
		int res;
		if (crs(u, v) == 0) {
			res = 2;
		} else if (dot(u, v) == 0) {
			res = 1;
		} else {
			res = 0;
		}
		cout << res << '\n';
	}

	return 0;
}