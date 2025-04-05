// verification-helper: PROBLEM https://judge.yosupo.jp/problem/static_convex_hull

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "geometry/polygonal.hpp"

using geometry::convex;
using geometry::Point;

int main() {
    std::ios_base::sync_with_stdio(false);

    auto sc = fast_input::Scanner();

    using P = Point<i64>;

    int T;
    sc >> T;
    while (T--) {
        int N;
        sc >> N;
        auto pts = Vec<P>(N);
        for (auto& [x, y] : pts) {
            sc >> x >> y;
        }

        auto ch = convex(pts);
        std::cout << size(ch) << '\n';
        for (auto [x, y] : ch) {
            std::cout << x << ' ' << y << '\n';
        }
    }

    return 0;
}