// verification-helper: PROBLEM https://judge.yosupo.jp/problem/furthest_pair

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "geometry/base.hpp"
#include "geometry/polygonal.hpp"

using geometry::diameter;
using geometry::Point;

using P = Point<i64>;

pair<int, int> solve(const Vec<P>& pts) {
    Vec<P> ch = convex(pts);
    assert(size(ch) >= 1);
    if (size(ch) == 1) {
        return {0, 1};
    }

    P p0 = ch[0];
    P p1 = ch[1];
    i64 best = dist2(p0 - p1);
    diameter(ch, [&](P a, P b) {
        i64 d = dist2(a - b);
        if (d > best) {
            best = d;
            p0 = a;
            p1 = b;
        }
    });

    auto get_idx = [&](const P& p) -> int {
        return int(std::find(begin(pts), end(pts), p) - begin(pts));
    };
    return {get_idx(p0), get_idx(p1)};
}

int main() {
    auto sc = fast_input::Scanner();

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