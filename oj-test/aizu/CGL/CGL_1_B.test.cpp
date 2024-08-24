// verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_B
// verification-helper: ERROR 0.000000001

#include "contest/base.hpp"
#include "geometry/base.hpp"
#include "geometry/linear.hpp"
using namespace std;

using geometry::project;

using Real = double;
using P = geometry::Point<Real>;
using L = geometry::L<Real>;

int main() {
	cout << fixed << setprecision(20);

	P p1, p2;
	cin >> p1 >> p2;
	auto l = L(p1, p2);

	int Q;
	cin >> Q;
	while (Q--) {
		P p;
		cin >> p;

		P proj = project(l, p);
		P refl = proj * 2 - p;
		cout << refl.x << ' ' << refl.y << '\n';
	}

	return 0;
}