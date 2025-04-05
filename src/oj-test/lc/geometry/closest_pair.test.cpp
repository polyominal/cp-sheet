// verification-helper: PROBLEM https://judge.yosupo.jp/problem/closest_pair

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "geometry/base.hpp"
#include "geometry/closest-pair.hpp"

using geometry::closest_pair;
using geometry::Point;

using P = Point<i64>;

pair<int, int> solve(const Vec<P>& pts) {
    auto p0 = pts[0];
    auto p1 = pts[1];
    closest_pair(pts, [&](P a, P b) { p0 = a, p1 = b; });
    if (p0 != p1) {
        auto get_idx = [&](const P& p) -> int {
            return int(std::find(begin(pts), end(pts), p) - begin(pts));
        };
        return {get_idx(p0), get_idx(p1)};
    } else {
        // must find two different indices
        auto it0 = std::find(begin(pts), end(pts), p0);
        auto it1 = std::find(next(it0), end(pts), p0);
        return {int(it0 - begin(pts)), int(it1 - begin(pts))};
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    auto sc = fast_input::Scanner(stdin);

    int T;
    sc >> T;
    while (T--) {
        int N;
        sc >> N;
        auto pts = Vec<P>(N);
        for (auto& [x, y] : pts) {
            sc >> x >> y;
        }

        auto res = solve(pts);
        std::cout << res.first << ' ' << res.second << '\n';
    }

    return 0;
}